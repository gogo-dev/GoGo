#include <database/MySQLGunzDB.h>

#include <cstddef>
#include <cassert>

#include <boost/bind/bind.hpp>
#include <boost/function.hpp>

using namespace std;
using namespace boost;
using namespace mysqlpp;

static void make_get_equipment_query(Query& q, uint32_t cid)
{
	q << "SELECT * from character_equip where charid=" << cid;
}

static SmallVector<Item, 12> handle_get_equipment(const StoreQueryResult& result)
{
	size_t rowCount = result.num_rows();
	assert(rowCount < 2);

	SmallVector<Item, 12> ret;

	if(rowCount == 0)
		return ret;

	const Row& row = result[0];

	Item temp;
	for(size_t i = 1, size = row.size(); i < size; ++i)
	{
		// TODO: Populate the items with REAL information.
		temp.ItemID = 0xFFFFFFFF;
		temp.Level = 0xFF;
		temp.MaxWT = 0xFFFFFFFF;
		temp.Price = 0xFFFFFFFF;
		temp.RentHour = 0xFFFFFFFF;
		temp.Sex = 0xFF;
		temp.Weight = 0xFFFFFFFF;

		temp.ItemCID = row[i];
		ret.push_back(temp);
	}

	return ret;
}

SmallVector<Item, 12> MySQLGunzDB::GetEquipment(uint32_t cid)
{
	return run_query<SmallVector<Item, 12> >(
		bind(make_get_equipment_query, _1, cid),
		handle_get_equipment
	);
}
