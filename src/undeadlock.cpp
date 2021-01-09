/*
 * undeadlock.cpp
 *
 *  Created on: Jul 29, 2017
 *      Author: nullifiedcat
 */

#include "ipcb.hpp"
#include "cathookipc.hpp"

int main() {
    peer_cl = new peer_t(SERVER_NAME, false, false);
    if (!peer_cl->Connect(-1)) {
        delete peer_cl;
        peer_cl = nullptr;
        printf("Failed to connect to IPC");
        return 1;
    }

	pthread_mutex_unlock(&peer_cl->memory->mutex);
    delete peer_cl;
    peer_cl = nullptr;
    return 0;
}
