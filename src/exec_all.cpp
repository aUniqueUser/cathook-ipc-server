/*
 * exec_all.cpp
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
    if (argc != 2) {
        printf("Bad number of arguments!");
        return 1;
    }

    peer_cl = new peer_t(SERVER_NAME, false, false);
    if (!peer_cl->Connect(-1)) {
        delete peer_cl;
        peer_cl = nullptr;
        printf("Failed to connect to IPC");
        return 1;
    }

    std::string command = std::string(argv[1]);
    ReplaceString(command, " && ", " ; ");
    if (command.length() >= 63) {
        peer_cl->SendMessage(0, -1, ipc_commands::execute_client_cmd_long, command.c_str(), command.length() + 1);
    } else {
        peer_cl->SendMessage(command.c_str(), -1, ipc_commands::execute_client_cmd, 0, 0);
    }

    printf("Executed \"%s\" on all peers", command.c_str());
    delete peer_cl;
    peer_cl = nullptr;
    return 0;
}
