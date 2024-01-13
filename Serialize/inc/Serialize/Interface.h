#pragma once
#include <string>
#include <memory>
#include <vector>

namespace Serialize
{
	class Map;
	class Serializable
	{
	public:
		using uptr = std::unique_ptr<Serializable>;
		virtual void Serialize(Map& data) const = 0;
		virtual ~Serializable() = default;
	};

	class Map;
	class List
	{
	public:
		virtual void emplace_back(std::string const& value) = 0;	
		virtual void emplace_back(Serializable const& value) = 0;

		virtual std::unique_ptr<Map> MapNode() = 0;
		virtual std::unique_ptr<List> ListNode() = 0;

		virtual ~List() = default;
	};

	class Map
	{
	public:
		virtual void set(std::string const& tag, std::string const& value) = 0;
		virtual void set(std::string const& tag, Serializable const& value) = 0;

		virtual std::unique_ptr<Map> MapNode(const char* const tag) = 0;
		virtual std::unique_ptr<List> ListNode(const char* const tag) = 0;

		virtual ~Map() = default;
	};

	class Deserializer
	{
	public:
		using uptr = std::unique_ptr<Deserializer>;
		virtual std::string get(std::string tag) const = 0;
		virtual std::vector<std::string> getList(std::string tag) const = 0;
		virtual std::vector<std::string> getList() const = 0;

		virtual uptr getElement(std::string tag) const = 0;
		virtual std::vector<uptr> GetElementList(std::string tag) const = 0;
		virtual std::vector<uptr> GetElementList() const = 0;
	
		virtual ~Deserializer() = default;
	};
}