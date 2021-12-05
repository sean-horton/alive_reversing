#include "../../AliveLibCommon/stdafx_common.h"
#include "relive_api.hpp"
#include "../../AliveLibAE/Path.hpp"
#include "../../AliveLibAE/PathData.hpp"
#include "../../AliveLibAO/Collisions.hpp"
#include "../../AliveLibAE/Collisions.hpp"
#include "LvlReaderWriter.hpp"
#include "JsonUpgraderAO.hpp"
#include "JsonUpgraderAE.hpp"
#include "JsonModelTypes.hpp"
#include "JsonReaderAE.hpp"
#include "JsonReaderAO.hpp"
#include "JsonWriterAE.hpp"
#include "JsonWriterAO.hpp"
#include "JsonMapRootInfoReader.hpp"
#include "TypesCollectionBase.hpp"
#include "Base64.hpp"
#include <iostream>
#include <gmock/gmock.h>
#include <type_traits>
#include <typeindex>
#include <lodepng/lodepng.h>

bool RunningAsInjectedDll()
{
    return false;
}

// items defined to avoid having to link AliveLibAO
namespace AO {
    const PathFunctionTable kObjectFactory = {};

    void CC Collisions::Factory_40CEC0(const CollisionInfo* , const u8* )
    {

    }
} // namespace AO

// ditto for AliveLibAe
const PathFunctionTable kObjectFactory = {};

// ditto for AliveLibCommon
[[noreturn]] void ALIVE_FATAL(const char_type*)
{
    abort();
}

void CC Collisions::Factory_4188A0(const CollisionInfo*, const u8*)
{

}

namespace ReliveAPI {
struct PathBND
{
    std::string mPathBndName;
    std::vector<s32> mPaths;
    std::vector<u8> mFileData;
    PathInfo mPathInfo;
};

[[nodiscard]] static PathInfo ToPathInfo(const AO::PathData& data, const AO::CollisionInfo& collisionInfo)
{
    PathInfo info = {};
    info.mGridWidth = data.field_C_grid_width;
    info.mGridHeight = data.field_E_grid_height;
    info.mWidth = (data.field_8_bTop - data.field_4_bLeft) / data.field_C_grid_width;
    info.mHeight = (data.field_A_bBottom - data.field_6_bRight) / data.field_E_grid_height;
    info.mIndexTableOffset = data.field_18_object_index_table_offset;
    info.mObjectOffset = data.field_14_object_offset;

    info.mNumCollisionItems = collisionInfo.field_10_num_collision_items;
    info.mCollisionOffset = collisionInfo.field_C_collision_offset;

    return info;
}


[[nodiscard]] static PathInfo ToPathInfo(const PathData& data, const CollisionInfo& collisionInfo)
{
    PathInfo info = {};
    info.mGridWidth = data.field_A_grid_width;
    info.mGridHeight = data.field_C_grid_height;
    info.mWidth = (data.field_4_bTop - data.field_0_bLeft) / data.field_A_grid_width;
    info.mHeight = (data.field_6_bBottom - data.field_2_bRight) / data.field_C_grid_height;
    info.mIndexTableOffset = data.field_16_object_indextable_offset;
    info.mObjectOffset = data.field_12_object_offset;

    info.mNumCollisionItems = collisionInfo.field_10_num_collision_items;
    info.mCollisionOffset = collisionInfo.field_C_collision_offset;

    return info;
}

class PathBlyRecAdapter
{
public:
    explicit PathBlyRecAdapter(const AO::PathBlyRec* pBlyRec)
        : mBlyRecAO(pBlyRec)
    {
    }

    explicit PathBlyRecAdapter(const PathBlyRec* pBlyRec)
        : mBlyRecAE(pBlyRec)
    {
    }

    const char_type* BlyName() const
    {
        return mBlyRecAO ? mBlyRecAO->field_0_blyName : mBlyRecAE->field_0_blyName;
    }

    PathInfo ConvertPathInfo() const
    {
        return mBlyRecAO ? ToPathInfo(*mBlyRecAO->field_4_pPathData, *mBlyRecAO->field_8_pCollisionData) : ToPathInfo(*mBlyRecAE->field_4_pPathData, *mBlyRecAE->field_8_pCollisionData);
    }

private:
    const AO::PathBlyRec* mBlyRecAO = nullptr;
    const PathBlyRec* mBlyRecAE = nullptr;
};

class PathRootAdapter
{
public:
    explicit PathRootAdapter(AO::PathRoot* pRoot)
        : mRootAO(pRoot)
    {
    }

    explicit PathRootAdapter(PathRoot* pRoot)
        : mRootAE(pRoot)
    {
    }

    const char_type* BndName() const
    {
        return mRootAO ? mRootAO->field_38_bnd_name : mRootAE->field_38_bnd_name;
    }

    s32 PathCount() const
    {
        return mRootAO ? mRootAO->field_18_num_paths : mRootAE->field_18_num_paths;
    }

    PathBlyRecAdapter PathAt(s32 idx) const
    {
        return mRootAO ? PathBlyRecAdapter(&mRootAO->field_0_pBlyArrayPtr[idx]) : PathBlyRecAdapter(&mRootAE->field_0_pBlyArrayPtr[idx]);
    }

private:
    AO::PathRoot* mRootAO = nullptr;
    PathRoot* mRootAE = nullptr;
};

class PathRootContainerAdapter
{
public:
    explicit PathRootContainerAdapter(Game gameType)
        : mGameType(gameType)
    {
    }

    s32 PathRootCount() const
    {
        return mGameType == Game::AO ? ALIVE_COUNTOF(AO::gMapData_4CAB58.paths) : ALIVE_COUNTOF(sPathData_559660.paths);
    }

    PathRootAdapter PathAt(s32 idx) const
    {
        return mGameType == Game::AO ? PathRootAdapter(&AO::gMapData_4CAB58.paths[idx]) : PathRootAdapter(&sPathData_559660.paths[idx]);
    }

private:
    Game mGameType = {};
};

enum class OpenPathBndResult
{
    OK,
    PathResourceChunkNotFound,
    NoPaths
};

[[nodiscard]] static OpenPathBndResult OpenPathBndGeneric(std::vector<u8>& fileDataBuffer, PathBND& ret, LvlReader& lvl, Game game, s32* pathId)
{
    const PathRootContainerAdapter adapter(game);
    for (s32 i = 0; i < adapter.PathRootCount(); ++i)
    {
        const auto pathRoot = adapter.PathAt(i);
        if (!pathRoot.BndName())
        {
            continue;
        }

        // Try to open the BND
        const bool goodRead = lvl.ReadFileInto(fileDataBuffer, pathRoot.BndName());
        if (!goodRead)
        {
            continue;
        }

        ret.mPathBndName = pathRoot.BndName();
        if (pathId)
        {
            // Open the specific path if we have one
            ChunkedLvlFile pathChunks(fileDataBuffer);
            std::optional<LvlFileChunk> chunk = pathChunks.ChunkById(*pathId);
            if (!chunk)
            {
                return OpenPathBndResult::PathResourceChunkNotFound;
            }

            // Save the actual path resource block data
            ret.mFileData = std::move(chunk)->Data();

            // Path id in range?
            if (*pathId >= 0 && *pathId <= pathRoot.PathCount())
            {
                // Path at this id have a name?
                const PathBlyRecAdapter pBlyRec = pathRoot.PathAt(*pathId);
                if (pBlyRec.BlyName())
                {
                    // Copy out its info
                    ret.mPathBndName = pathRoot.BndName();
                    ret.mPathInfo = pBlyRec.ConvertPathInfo();
                    return OpenPathBndResult::OK;
                }
            }

            // Path id out of bounds or the entry is blank
            return OpenPathBndResult::PathResourceChunkNotFound;
        }

        // Add all path ids
        for (s32 j = 1; j <= pathRoot.PathCount(); ++j)
        {
            // Only add paths that are not blank entries
            const PathBlyRecAdapter pBlyRec = pathRoot.PathAt(j);
            if (pBlyRec.BlyName())
            {
                ret.mPaths.push_back(j);
            }
        }

        return OpenPathBndResult::OK;
    }

    return OpenPathBndResult::NoPaths;
}

[[nodiscard]] static PathBND OpenPathBnd(LvlReader& lvlReader, std::vector<u8>& fileDataBuffer, Game& game, s32* pathId)
{
    PathBND ret = {};

    // Find AE Path BND
    if (OpenPathBndGeneric(fileDataBuffer, ret, lvlReader, Game::AE, pathId) == OpenPathBndResult::OK)
    {
        game = Game::AE;
        return ret;
    }

    // Failed, look for AO Path BND
    if (OpenPathBndGeneric(fileDataBuffer, ret, lvlReader, Game::AO, pathId) == OpenPathBndResult::OK)
    {
        game = Game::AO;
        return ret;
    }

    // Both failed
    throw ReliveAPI::OpenPathException();
}

void DebugDumpTlvs(const std::string& prefix, const std::string& lvlFile, s32 pathId)
{
    Game game = {};

    LvlReader lvl(lvlFile.c_str());
    std::vector<u8> buffer;
    ReliveAPI::PathBND pathBnd = ReliveAPI::OpenPathBnd(lvl, buffer, game, &pathId);

    if (game == Game::AO)
    {
        JsonWriterAO doc(pathId, pathBnd.mPathBndName, pathBnd.mPathInfo);
        doc.DebugDumpTlvs(prefix, pathBnd.mPathInfo, pathBnd.mFileData);
    }
    else
    {
        JsonWriterAE doc(pathId, pathBnd.mPathBndName, pathBnd.mPathInfo);
        doc.DebugDumpTlvs(prefix, pathBnd.mPathInfo, pathBnd.mFileData);
    }
}

// Increment when a breaking change to the JSON is made and implement an
// upgrade step that converts from the last version to the current.
constexpr s32 kApiVersion = 1;

[[nodiscard]] s32 GetApiVersion()
{
    return kApiVersion;
}

void ExportPathBinaryToJson(std::vector<u8>& fileDataBuffer, const std::string& jsonOutputFile, const std::string& inputLvlFile, s32 pathResourceId)
{
    Game game = {};

    LvlReader lvl(inputLvlFile.c_str());
    ReliveAPI::PathBND pathBnd = ReliveAPI::OpenPathBnd(lvl, fileDataBuffer, game, &pathResourceId);

    if (game == Game::AO)
    {
        JsonWriterAO doc(pathResourceId, pathBnd.mPathBndName, pathBnd.mPathInfo);
        doc.Save(fileDataBuffer, lvl, pathBnd.mPathInfo, pathBnd.mFileData, jsonOutputFile);
    }
    else
    {
        JsonWriterAE doc(pathResourceId, pathBnd.mPathBndName, pathBnd.mPathInfo);
        doc.Save(fileDataBuffer, lvl, pathBnd.mPathInfo, pathBnd.mFileData, jsonOutputFile);
    }
}

void ExportPathBinaryToJson(const std::string& jsonOutputFile, const std::string& inputLvlFile, s32 pathResourceId)
{
    std::vector<u8> buffer;
    ExportPathBinaryToJson(buffer, jsonOutputFile, inputLvlFile, pathResourceId);
}

void UpgradePathJson(const std::string& jsonFile)
{
    JsonMapRootInfoReader rootInfo;
    rootInfo.Read(jsonFile);

    if (rootInfo.mMapRootInfo.mGame == "AO")
    {
        JsonUpgraderAO upgrader;
        upgrader.Upgrade(jsonFile, rootInfo.mMapRootInfo.mVersion, GetApiVersion());
    }
    else
    {
        JsonUpgraderAE upgrader;
        upgrader.Upgrade(jsonFile, rootInfo.mMapRootInfo.mVersion, GetApiVersion());
    }
}

template <typename ReturnType, typename ContainerType>
static ReturnType* ItemAtXY(ContainerType& container, s32 x, s32 y)
{
    for (auto& iteratedItem : container)
    {
        if (iteratedItem.x == x && iteratedItem.y == y)
        {
            return &iteratedItem;
        }
    }
    return nullptr;
}

template <typename ItemType, typename ContainerType, typename FnOnItem>
static void ForEachItemAtXY(const PathInfo& pathInfo, ContainerType& container, FnOnItem onItem)
{
    for (s32 y = 0; y < pathInfo.mHeight; y++)
    {
        for (s32 x = 0; x < pathInfo.mWidth; x++)
        {
            auto item = ItemAtXY<ItemType>(container, x, y);
            if (item)
            {
                onItem(*item);
            }
        }
    }
}

static void WriteCollisionLine(ByteStream& s, const AO::PathLine& line)
{
    s.Write(line.field_0_rect.x);
    s.Write(line.field_0_rect.y);
    s.Write(line.field_0_rect.w);
    s.Write(line.field_0_rect.h);

    s.Write(line.field_8_type);
    s.Write(line.field_9_pad);
    s.Write(line.field_A_pad);
    s.Write(line.field_B_pad);

    s.Write(line.field_C_previous);
    s.Write(line.field_10_next);
}

static void WriteCollisionLine(ByteStream& s, const ::PathLine& line)
{
    s.Write(line.field_0_rect.x);
    s.Write(line.field_0_rect.y);
    s.Write(line.field_0_rect.w);
    s.Write(line.field_0_rect.h);

    s.Write(line.field_8_type);
    s.Write(line.field_9_padding);

    s.Write(line.field_A_previous);
    s.Write(line.field_C_next);

    s.Write(line.field_E_previous2);
    s.Write(line.field_10_next2);

    s.Write(line.field_12_line_length);
}

static u32 CamBitsIdFromName(const std::string& pCamName)
{
    if (pCamName.length() < 7)
    {
        // todo: throw
        LOG_WARNING("Bad camera name, can't get resource id " << pCamName);
        return 0;
    }
    // Given R1P20C15 returns 2015
    return 1 * (pCamName[7] - '0') + 10 * (pCamName[6] - '0') + 100 * (pCamName[4] - '0') + 1000 * (pCamName[3] - '0');
}

static u16 RGB888ToRGB565(const u8* rgb888Pixel)
{
    const u8 red = rgb888Pixel[0];
    const u8 green = rgb888Pixel[1];
    const u8 blue = rgb888Pixel[2];

    const u16 b = (blue >> 3) & 0x1f;
    const u16 g = ((green >> 2) & 0x3f) << 5;
    const u16 r = ((red >> 3) & 0x1f) << 11;

    return (r | g | b);
}

static void ImportCamerasAndFG1(std::vector<u8>& fileDataBuffer, LvlWriter& inputLvl, const std::vector<CameraNameAndTlvBlob>& camerasAndMapObjects)
{
    // Rebuild cameras/FG1 and embedded resource blocks
    for (const CameraNameAndTlvBlob& camIter : camerasAndMapObjects)
    {
        // Get camera ID from the name for the Bits chunk
        if (!camIter.mName.empty())
        {
            const u32 bitsId = CamBitsIdFromName(camIter.mName);

            // Load existing .CAM if possible so existing additional resource blocks don't get removed by
            // re-creating the CAM from scratch.
            ChunkedLvlFile camFile;
            if (inputLvl.ReadFileInto(fileDataBuffer, (camIter.mName + ".CAM").c_str()))
            {
                camFile = ChunkedLvlFile(fileDataBuffer);
            }

            unsigned width = 0;
            unsigned height = 0;
            std::vector<u8> rawPixels;
            std::vector<u8> pngData = FromBase64(camIter.mCameraImage);
            const auto error = lodepng::decode(rawPixels, width, height, pngData, LCT_RGBA, 8);
            if (error)
            {
                // todo: throw
            }

            if (width != 640 || height != 240)
            {
                // todo: throw
            }

            // Arrage pixel data in strips and RGB888 -> RGB565
            struct CamStrip final
            {
                u16 mStripLen = 16 * 240 * sizeof(u16);
                u16 mStrip[240][16] = {};
            };

            struct CamImageStrips final
            {
            public:
                void SetPixel(u32 x, u32 y, u16 pixel)
                {
                    const u32 stripNum = x / 16;
                    const u32 xPixel = x % 16;
                    mStrips[stripNum].mStrip[y][xPixel] = pixel;
                }

                std::vector<u8> ToVector() const
                {
                    std::vector<u8> r;
                    const u32 totalLengthDataSize = (640 / 16) * sizeof(u16);
                    const u32 totalStripDataSize = (640 / 16) * (16 * 240) * sizeof(u16);
                    r.resize(totalLengthDataSize + totalStripDataSize);

                    u16* pStream = reinterpret_cast<u16*>(r.data());

                    u32 pos = 0;
                    for (u32 i = 0; i < 640 / 16; i++)
                    {
                        pStream[pos] = mStrips[i].mStripLen;
                        pos++;

                        memcpy(pStream + pos, &mStrips[i].mStrip[0][0], mStrips[i].mStripLen);
                        pos += mStrips[i].mStripLen / sizeof(u16);
                    }
                    return r;
                }

            private:
                CamStrip mStrips[640 / 16];
            };

            CamImageStrips bitsData;
            for (u32 x = 0; x < 640; x++)
            {
                for (u32 y = 0; y < 240; y++)
                {
                    const u32* pPixel32 = &reinterpret_cast<const u32*>(rawPixels.data())[To1dIndex(640, x, y)];
                    bitsData.SetPixel(x, y, RGB888ToRGB565(reinterpret_cast<const u8*>(pPixel32)));
                }
            }

            LvlFileChunk bitsChunk(bitsId, ResourceManager::Resource_Bits, bitsData.ToVector());
            camFile.AddChunk(std::move(bitsChunk));

            // TODO: Remove FG1 blocks

            // TODO: FG1 blocks use id BitsId << 8 + idx

            // TODO: Iterate in 32x16 blocks, creating full or partial blocks as needed

            // TODO: Add reconstructed single FG1 block

            // Add or update the CAM file
            inputLvl.AddFile((camIter.mName + ".CAM").c_str(), camFile.Data());
        }
    }
}

template <typename JsonReaderType>
static void SaveBinaryPathToLvl(std::vector<u8>& fileDataBuffer, Game gameType, const std::string& jsonInputFile, const std::string& inputLvlFile, const std::string& outputLvlFile, bool skipCamsAndFG1)
{
    JsonReaderType doc;
    auto [camerasAndMapObjects, collisionLines] = doc.Load(jsonInputFile);

    LvlWriter inputLvl(inputLvlFile.c_str());
    if (!inputLvl.IsOpen())
    {
        throw ReliveAPI::IOReadException(inputLvlFile.c_str());
    }

    std::optional<std::vector<u8>> oldPathBnd = inputLvl.ReadFile(doc.mRootInfo.mPathBnd.c_str());
    if (!oldPathBnd)
    {
        throw ReliveAPI::OpenPathException();
    }

    ChunkedLvlFile pathBndFile(*oldPathBnd);
    std::optional<LvlFileChunk> chunk = pathBndFile.ChunkById(doc.mRootInfo.mPathId);
    if (!chunk)
    {
        throw ReliveAPI::OpenPathException();
    }

    PathRootContainerAdapter pathRootContainer(gameType);
    std::optional<PathBlyRecAdapter> pathBlyRecAdapter;
    for (s32 i = 0; i < pathRootContainer.PathRootCount(); i++)
    {
        PathRootAdapter pathRoot = pathRootContainer.PathAt(i);
        if (pathRoot.BndName())
        {
            if (doc.mRootInfo.mPathBnd == pathRoot.BndName())
            {
                if (doc.mRootInfo.mPathId >= 0 && doc.mRootInfo.mPathId <= pathRoot.PathCount())
                {
                    pathBlyRecAdapter = pathRoot.PathAt(doc.mRootInfo.mPathId);
                    break;
                }
            }
        }
    }

    if (!pathBlyRecAdapter)
    {
        throw ReliveAPI::OpenPathException();
    }

    const PathInfo pathInfo = pathBlyRecAdapter->ConvertPathInfo();

    ByteStream s;
    s.ReserveSize(1024 * 20); // 20 kb estimate

    // Write camera array
    for (s32 y = 0; y < pathInfo.mHeight; y++)
    {
        for (s32 x = 0; x < pathInfo.mWidth; x++)
        {
            CameraNameAndTlvBlob* pItem = ItemAtXY<CameraNameAndTlvBlob>(camerasAndMapObjects, x, y);
            if (pItem)
            {
                // We have a camera
                if (pItem->mName.empty())
                {
                    // With a blank name
                    const static u8 blank[8] = {};
                    s.Write(blank);
                }
                else if (pItem->mName.length() == 8)
                {
                    // With a non blank name
                    s.Write(pItem->mName);
                }
                else
                {
                    // With a name that isn't 8 chars
                    throw ReliveAPI::BadCameraNameException(pItem->mName);
                }
            }
            else
            {
                // No camera
                const static u8 blank[8] = {};
                s.Write(blank);
            }
        }
    }

    if (static_cast<s32>(collisionLines.size()) != pathInfo.mNumCollisionItems)
    {
        throw ReliveAPI::CollisionsCountChangedException();
    }

    // Write collision lines
    for (const auto& line : collisionLines)
    {
        WriteCollisionLine(s, line);
    }

    struct IndexTableEntry
    {
        s32 x = 0;
        s32 y = 0;
        s32 objectsOffset = 0;
    };

    // Write object lists for each camera, either put everything before the index table if it fits, or put
    // everything after the index table as the game can enumerate ALL tlvs in one go. Thus splitting it across the index table
    // area would break that logic.
    // Additionally construct the index table offsets as we go.
    std::size_t allTlvsLen = 0;
    for (const CameraNameAndTlvBlob& camIter : camerasAndMapObjects)
    {
        allTlvsLen += camIter.TotalTlvSize();
    }

    // Data would overwrite the index table, put everything after it
    if (allTlvsLen + pathInfo.mObjectOffset > pathInfo.mIndexTableOffset)
    {
        s.SeekWrite(pathInfo.mObjectOffset + (sizeof(s32) * pathInfo.mWidth * pathInfo.mHeight));
    }

    std::vector<IndexTableEntry> indexTable;
    for (s32 y = 0; y < pathInfo.mHeight; y++)
    {
        for (s32 x = 0; x < pathInfo.mWidth; x++)
        {
            CameraNameAndTlvBlob* pItem = ItemAtXY<CameraNameAndTlvBlob>(camerasAndMapObjects, x, y);
            if (pItem)
            {
                if (pItem->mTlvBlobs.empty())
                {
                    // Dont add a table entry for a camera that has no TLV data
                    indexTable.push_back({x, y, -1});
                }
                else
                {
                    const s32 objDataOff = static_cast<s32>(s.WritePos()) - static_cast<s32>(pathInfo.mObjectOffset);
                    indexTable.push_back({x, y, objDataOff});
                    for (const auto& tlv : pItem->mTlvBlobs)
                    {
                        s.Write(tlv);
                    }
                }
            }
            else
            {
                indexTable.push_back({x, y, -1});
            }
        }
    }

    // Write index table values we just populated at the correct offset
    s.SeekWrite(pathInfo.mIndexTableOffset);
    ForEachItemAtXY<IndexTableEntry>(pathInfo, indexTable, [&](const IndexTableEntry& tableEntry)
                                     { s.Write(tableEntry.objectsOffset); });

    // Push the path resource into a file chunk
    LvlFileChunk newPathBlock(doc.mRootInfo.mPathId, ResourceManager::ResourceType::Resource_Path, std::move(s).GetBuffer());

    // Add or replace the original file chunk
    pathBndFile.AddChunk(std::move(newPathBlock));

    // Add or replace the original path BND in the lvl
    inputLvl.AddFile(doc.mRootInfo.mPathBnd.c_str(), std::move(pathBndFile).Data());

    if (!skipCamsAndFG1)
    {
        ImportCamerasAndFG1(fileDataBuffer, inputLvl, camerasAndMapObjects);
    }

    // Write out the updated lvl to disk
    if (!inputLvl.Save(fileDataBuffer, outputLvlFile.c_str()))
    {
        throw ReliveAPI::IOWriteException(outputLvlFile.c_str());
    }
}

void ImportPathJsonToBinary(std::vector<u8>& fileDataBuffer, const std::string& jsonInputFile, const std::string& inputLvl, const std::string& outputLvlFile, const std::vector<std::string>& /*lvlResourceSources*/, bool skipCamerasAndFG1)
{
    JsonMapRootInfoReader rootInfo;
    rootInfo.Read(jsonInputFile);

    if (rootInfo.mMapRootInfo.mVersion != GetApiVersion())
    {
        throw ReliveAPI::JsonNeedsUpgradingException();
    }

    if (rootInfo.mMapRootInfo.mGame == "AO")
    {
        SaveBinaryPathToLvl<JsonReaderAO>(fileDataBuffer, Game::AO, jsonInputFile, inputLvl, outputLvlFile, skipCamerasAndFG1);
    }
    else
    {
        SaveBinaryPathToLvl<JsonReaderAE>(fileDataBuffer, Game::AE, jsonInputFile, inputLvl, outputLvlFile, skipCamerasAndFG1);
    }
}

void ImportPathJsonToBinary(const std::string& jsonInputFile, const std::string& inputLvl, const std::string& outputLvlFile, const std::vector<std::string>& lvlResourceSources)
{
    std::vector<u8> buffer;
    ImportPathJsonToBinary(buffer, jsonInputFile, inputLvl, outputLvlFile, lvlResourceSources, false);
}

[[nodiscard]] EnumeratePathsResult EnumeratePaths(std::vector<u8>& fileDataBuffer, const std::string& inputLvlFile)
{
    EnumeratePathsResult ret = {};
    Game game = {};

    LvlReader lvl(inputLvlFile.c_str());
    PathBND pathBnd = OpenPathBnd(lvl, fileDataBuffer, game, nullptr);
    ret.paths = pathBnd.mPaths;
    ret.pathBndName = pathBnd.mPathBndName;
    return ret;
}

[[nodiscard]] EnumeratePathsResult EnumeratePaths(const std::string& inputLvlFile)
{
    std::vector<u8> buffer;
    return EnumeratePaths(buffer, inputLvlFile);
}
} // namespace ReliveAPI
