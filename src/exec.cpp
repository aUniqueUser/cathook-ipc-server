/*
 * exec.cpp
 *
 *  Created on: Jul 29, 2017
 *      Author: nullifiedcat
 */

#include "ipcb.hpp"
#include "cathookipc.hpp"

#include <string>
#include <stdio.h>

void ReplaceString(std::string& input, const std::string& what, const std::string& with_what) {
	size_t index;
	index = input.find(what);
	while (index != std::string::npos) {
		input.replace(index, what.size(), with_what);
		index = input.find(what, index + with_what.size());
	}
}

int main(int argc, const char** argv) {
    if (argc != 3) {
        printf("Bad number of arguments!");
        return 1;
    }

    char* endptr = nullptr;
    unsigned target_id = strtol(argv[1], &endptr, 10);
    if (endptr == argv[1]) {
        printf("Target id is NaN!\n");
        return 1;
    }
    if (target_id > 255) {
        printf("Invalid target id: %u\n", target_id);
        return 1;
    }

    peer_cl = new peer_t(SERVER_NAME, false, false);
    if (!peer_cl->Connect(-1)) {
        delete peer_cl;
        peer_cl = nullptr;
        printf("Failed to connect to IPC");
        return 1;
    }

    std::string command = std::string(argv[2]);
    ReplaceString(command, " && ", " ; ");
    if (command.length() >= 63) {
        peer_cl->SendMessage(0, target_id, ipc_commands::execute_client_cmd_long, command.c_str(), command.length() + 1);
    } else {
        peer_cl->SendMessage(command.c_str(), target_id, ipc_commands::execute_client_cmd, 0, 0);
    }

    printf("Executed \"%s\" on peer_cl %d", command.c_str(), target_id);
    delete peer_cl;
    peer_cl = nullptr;
    return 0;
}
