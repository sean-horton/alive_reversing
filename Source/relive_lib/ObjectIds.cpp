#include "stdafx.h"
#include "ObjectIds.hpp"
#include "../AliveLibCommon/Sys_common.hpp"
#include "../relive_lib/BaseGameObject.hpp"

static constexpr u32 kObjectIdsArrayStartingSize = 101;

ObjectIds sObjectIds{kObjectIdsArrayStartingSize};

ObjectIds::~ObjectIds()
{
    for (u32 i = 0; i < field_0_buffer_size; i++)
    {
        while (field_4_pBuffer[i])
        {
            // Keep a copy of the current item
            ObjectId_Record* pCurrent = field_4_pBuffer[i];

            // Set the array to point to the next item
            field_4_pBuffer[i] = pCurrent->field_8_pNext;

            // Now free current, repeat until everything is gone
            relive_delete pCurrent;
        }
    }

    // Free the backing array
    delete[] field_4_pBuffer;
}

ObjectIds::ObjectIds(u32 size)
    : field_0_buffer_size(size)
{
    // Allocate the array and set all items to nullptr
    field_4_pBuffer = new ObjectId_Record*[size];
    for (u32 i = 0; i < field_0_buffer_size; i++)
    {
        field_4_pBuffer[i] = nullptr;
    }
}

u32 ObjectIds::Id_To_Buffer_Size_Range(TObjectId_KeyType id)
{
    return id % field_0_buffer_size;
}

ObjectId_Record* ObjectIds::Find_By_Id(TObjectId_KeyType idToFind, ObjectId_Record** ppLastMatch)
{
    ObjectId_Record* pRecord = field_4_pBuffer[Id_To_Buffer_Size_Range(idToFind)];
    *ppLastMatch = nullptr;

    while (pRecord)
    {
        if (pRecord->field_0_id == idToFind)
        {
            return pRecord;
        }

        // Keep track of what it was so we can fix links when removing found items
        *ppLastMatch = pRecord;

        // Go to the next record
        pRecord = pRecord->field_8_pNext;
    }
    return nullptr;
}

void ObjectIds::Insert(TObjectId_KeyType nextId, BaseGameObject* pGameObj)
{
    // Create new record
    ObjectId_Record* pRec = relive_new ObjectId_Record();
    if (!pRec)
    {
        ALIVE_FATAL("OOM");
    }
    pRec->field_0_id = nextId;
    pRec->field_4_obj_ptr = pGameObj;

    // Insert and fix links
    const u32 id = Id_To_Buffer_Size_Range(nextId);

    pRec->field_8_pNext = field_4_pBuffer[id];
    field_4_pBuffer[id] = pRec;
}

s16 ObjectIds::Remove(TObjectId_KeyType idToRemove)
{
    // Find the record
    ObjectId_Record* pLastMatch = nullptr;
    ObjectId_Record* pFound = Find_By_Id(idToRemove, &pLastMatch);
    if (!pFound)
    {
        return 0;
    }

    // Fix the links
    const u32 idx = Id_To_Buffer_Size_Range(idToRemove);
    if (pLastMatch)
    {
        // There was an object before this, so point to the one after what we found
        // so we can remove it.
        pLastMatch->field_8_pNext = pFound->field_8_pNext;
    }
    else
    {
        // There was not an object before this, so set the root to point the one after
        // we found so we can remove it.
        field_4_pBuffer[idx] = pFound->field_8_pNext;
    }

    // Free the found record
    relive_delete pFound;

    return 1;
}

BaseGameObject* ObjectIds::Find_Impl(TObjectId_KeyType idToFind)
{
    BaseGameObject* pFound = nullptr;
    if (idToFind != -1)
    {
        ObjectId_Record* tmp = nullptr;
        ObjectId_Record* pRecord = Find_By_Id(idToFind, &tmp);
        if (pRecord)
        {
            pFound = pRecord->field_4_obj_ptr;
        }
    }
    return pFound;
}

BaseGameObject* ObjectIds::Find(TObjectId_KeyType idToFind, ReliveTypes type)
{
    BaseGameObject* pItem = Find_Impl(idToFind);
    if (pItem && pItem->Type() != type)
    {
        LOG_ERROR("Expected type " << static_cast<s32>(type) << " for object with id " << idToFind << " but got " << static_cast<s32>(pItem->Type()));
        ALIVE_FATAL("Wrong type!");
    }
    return pItem;
}

s32 ObjectIds::EnsureIdIsUnique(s32 nextId)
{
    ObjectId_Record* pRecord = field_4_pBuffer[Id_To_Buffer_Size_Range(nextId)];

    while (pRecord)
    {
        if (pRecord->field_0_id >= nextId) // We've found a value equal to or higher than the input id, to prevent duplicates we need to find the highest used ID and +1 that
        {
            return GetHighestUsedId() + 1;
        }

        // Go to the next record
        pRecord = pRecord->field_8_pNext;
    }

    return nextId;
}

s32 ObjectIds::GetHighestUsedId()
{
    s32 nextId = 0;
    for (u32 i = 0; i < field_0_buffer_size; i++)
    {
        ObjectId_Record* pRecord = field_4_pBuffer[i];

        while (pRecord)
        {
            if (pRecord->field_0_id > nextId)
            {
                nextId = pRecord->field_0_id;
            }

            // Go to the next record
            pRecord = pRecord->field_8_pNext;
        }
    }

    return nextId;
}