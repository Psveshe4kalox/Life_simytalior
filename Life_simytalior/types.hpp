#include <map>
#include <string>

namespace scu {

	struct Trait {
		std::wstring name;
		std::wstring description;
		std::int32_t value;
	};

	struct Choice {
		std::wstring description;

		std::map<std::string, std::int32_t> effects;
		std::map<std::string, std::int32_t> chains;
	};

	struct Event
	{
		std::wstring description;

		std::map<std::string, std::int32_t> conditions_traits_min;
		std::map<std::string, std::int32_t> conditions_traits_max;
		std::map<std::string, std::int32_t> conditions_chains;

		std::map<std::string, Choice> choices;

		// In month
		std::uint32_t age_increase;
	};

	struct Stage
	{
		std::wstring name;
		std::wstring description;

		// In month
		std::uint32_t min_age;
		std::uint32_t max_age;

		std::map<std::string, Event> events;
	};

	struct Ending
	{
		std::wstring description;

		bool is_condition_max = false;
		std::string condition_trait_id;
		std::int32_t condition_trait_value;
	};

	struct DeathDescription {
		/*DeathDescription(std::string, std::string, std::int32_t, std::int32_t) {

		}*/

		std::wstring description;
		std::string trait_id;
		std::int32_t min_value;
		std::int32_t max_value;
	};
}