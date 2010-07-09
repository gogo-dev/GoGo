#include <gunz/Stage.h>

namespace gunz {

Stage::Stage(const Traits& _traits)
	: traits(_traits)
{
}

Stage::Traits Stage::GetTraits() const
{
	return traits;
}

Stage::~Stage()
{
}

}
