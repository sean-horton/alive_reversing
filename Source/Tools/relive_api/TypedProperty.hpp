#pragma once

#include "BaseProperty.hpp"

#include <string>

namespace ReliveAPI {
class TypesCollectionBase;
class PropertyCollection;

template <typename T>
class TypedProperty final : public BaseProperty
{
public:
    TypedProperty(const std::string& name, const std::string& typeName, const char* idStr, bool isVisibleToEditor, T* data)
        : BaseProperty(name, typeName, idStr, isVisibleToEditor)
        , m_data(data)
    { }

    void Read(const PropertyCollection& propertyCollection, const TypesCollectionBase& types, const nlohmann::json& properties, Context& context) override;

    void Write(const PropertyCollection& propertyCollection, const TypesCollectionBase& types, nlohmann::json& properties, Context& context) override;

private:
    T* m_data = nullptr;
};
} // namespace ReliveAPI
