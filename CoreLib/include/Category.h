#ifndef CATEGORY_H
#define CATEGORY_H

namespace Category
{
	enum Type
	{
		None				= 0,
		Root				= 1 << 0,
		Scene				= 1 << 1,
		PlayerAircraft		= 1 << 2,
		AlliedAircraft		= 1 << 3,
		EnemyAircraft		= 1 << 4,
	};
}

#endif //CATEGORY_H