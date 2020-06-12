#include "Play.h"
#include "list.h"
#include "Query_Play_Persist.h"
#include <string.h>

int Play_Srv_FetchByName(play_list_t list, char condt[]) {
	return Play_Perst_SelectByName(list, condt);
}
