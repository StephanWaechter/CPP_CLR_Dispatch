#pragma once
#include "Serialize/Interface.h"
#include "nlohmann/json.hpp"
namespace Serialize
{
	class JsonListSerializer : public List
	{
	public:
		JsonListSerializer();
		~JsonListSerializer() override = default;

		void emplace_back(std::string const& value) override;
		void emplace_back(Serializable const& value) override;

		std::unique_ptr<Map> MapNode() override;
		std::unique_ptr<List> ListNode() override;

		inline nlohmann::json const& Json() const
		{
			return m_json;
		}

	private:
		nlohmann::json m_json;
		const char* const m_tag{ nullptr };
		nlohmann::json* m_root{ nullptr };
	};

	class JsonMapSerializer : public Map
	{
	public:
		JsonMapSerializer();
		~JsonMapSerializer() override = default;

		void set(std::string const& tag, std::string const& value) override;
		void set(std::string const& tag, Serializable const& value) override;

		std::unique_ptr<Map> MapNode(const char * const tag) override;
		std::unique_ptr<List> ListNode(const char* const tag) override;

		inline nlohmann::json const& Json() const
		{
			return m_json;
		}

	private:
		nlohmann::json m_json;
		const char* const m_tag{ nullptr };
		nlohmann::json* m_root{ nullptr };
	};

	class JsonListSerializerNode : public JsonListSerializer
	{
	public:
		JsonListSerializerNode(nlohmann::json* parent);
		JsonListSerializerNode(char const* const tag, nlohmann::json* parent);
		~JsonListSerializerNode() override;

	private:
		const char* const m_tag{ nullptr };
		nlohmann::json* m_root{ nullptr };
	};

	class JsonMapSerializerNode : public JsonMapSerializer
	{
	public:
		JsonMapSerializerNode(nlohmann::json* parent);
		JsonMapSerializerNode(char const* const tag, nlohmann::json* parent);
		~JsonMapSerializerNode() override;

	private:
		const char* const m_tag{ nullptr };
		nlohmann::json* m_root{ nullptr };
	};
}

