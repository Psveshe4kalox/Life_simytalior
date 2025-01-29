#include <map>
#include <vector>
#include <string>

#include "types.hpp"

namespace scu {

	struct Data
	{
		static const std::string age_trait_id;

		static const std::map<std::string, Trait> traits;
		static const std::map<std::string, Stage> stages;

		static const std::vector<Ending> endings;
		static const std::vector<DeathDescription> death_descriptions;
	};

}