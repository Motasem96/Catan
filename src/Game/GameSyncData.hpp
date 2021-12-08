#ifndef GAME_SYNC_DATA_HEADER
#define GAME_SYNC_DATA_HEADER
#include <mutex>

namespace Catan {
    struct GameSyncData {
        std::recursive_mutex g_myDataMutex;
    };
}
#endif