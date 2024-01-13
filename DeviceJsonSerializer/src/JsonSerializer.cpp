#include "Serialize/JsonSerializer.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace Serialize
{
	JsonListSerializer::JsonListSerializer() : m_json{}
	{
	}

	void JsonListSerializer::emplace_back(std::string const& value)
	{
		m_json.emplace_back(value);
	}

	void JsonListSerializer::emplace_back(Serializable const& value)
	{
		JsonMapSerializer serializer;
		value.Serialize(serializer);
		m_json.emplace_back(serializer.Json());
	}

	std::unique_ptr<Map> JsonListSerializer::MapNode()
	{
		return std::make_unique<JsonMapSerializerNode>(&m_json);
	}

	std::unique_ptr<List> JsonListSerializer::ListNode()
	{
		return std::make_unique<JsonListSerializerNode>(&m_json);
	}

	JsonMapSerializer::JsonMapSerializer() : m_json{}
	{
	}

	void JsonMapSerializer::set(std::string const& tag, std::string const& value)
	{
		m_json[tag] = value;
	}

	void JsonMapSerializer::set(std::string const& tag, Serializable const& value)
	{
		JsonMapSerializer serializer;
		value.Serialize(serializer);
		m_json[tag] = serializer.Json();
	}

	std::unique_ptr<Map> JsonMapSerializer::MapNode(const char* const tag)
	{
		return std::make_unique<JsonMapSerializerNode>(tag, &m_json);
	}

	std::unique_ptr<List> JsonMapSerializer::ListNode(const char* const tag)
	{
		return std::make_unique<JsonListSerializerNode>(tag, &m_json);
	}

	JsonListSerializerNode::JsonListSerializerNode(nlohmann::json* parent) : m_root{ parent }
	{
	}

	JsonListSerializerNode::JsonListSerializerNode(char const* const tag, nlohmann::json* parent) : m_tag{ tag }, m_root{ parent }
	{
	}

	JsonListSerializerNode::~JsonListSerializerNode()
	{
		if (m_root != nullptr)
		{
			if (m_tag != nullptr)
			{
				(*m_root)[m_tag] = Json();
			}
			else
			{
				m_root->emplace_back(Json());
			}
		}
	}

	JsonMapSerializerNode::JsonMapSerializerNode(nlohmann::json* parent) : m_root{ parent }
	{
	}

	JsonMapSerializerNode::JsonMapSerializerNode(char const* const tag, nlohmann::json* parent) : m_tag{ tag }, m_root{ parent }
	{
	}

	JsonMapSerializerNode::~JsonMapSerializerNode()
	{
		if (m_root != nullptr)
		{
			if (m_tag != nullptr)
			{
				m_root->at(m_tag) = Json();
			}
			else
			{
				m_root->emplace_back(Json());
			}
		}
	}


}
