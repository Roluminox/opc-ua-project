/**
 * @file client.cpp
 * @brief Simple OPC UA client that connects to a server and reads the "temperature" variable using open62541.
 *
 * This program creates an OPC UA client, connects to a local server, and reads the value of the "temperature" variable.
 */
#include <iostream>
#include <open62541/client.h>
#include <open62541/client_config_default.h>
#include <open62541/client_highlevel.h>

/**
 * @brief Main entry point for the OPC UA client.
 *
 * Connects to the server, reads the "temperature" variable, and waits for user input to exit.
 * @return Exit status code (0 if successful, error code otherwise)
 */
int main() {
    // Create and configure the OPC UA client
    UA_Client* client = UA_Client_new();
    UA_ClientConfig_setDefault(UA_Client_getConfig(client));

    // Connect to the OPC UA server (localhost:4840)
    UA_StatusCode status = UA_Client_connect(client, "opc.tcp://localhost:4840");
    if (status != UA_STATUSCODE_GOOD) {
        std::cerr << "Connection error: " << UA_StatusCode_name(status) << std::endl;
        UA_Client_delete(client);
        return 1;
    }

    // Read the "temperature" variable from the server
    UA_Variant value;
    UA_Variant_init(&value);

    UA_NodeId nodeId = UA_NODEID_STRING(1, (char*)"temperature"); /**< NodeId of the variable to read */
    status = UA_Client_readValueAttribute(client, nodeId, &value);
    if (status == UA_STATUSCODE_GOOD && UA_Variant_hasScalarType(&value, &UA_TYPES[UA_TYPES_DOUBLE])) {
        std::cout << "Temperature: " << *(UA_Double*)value.data << " °C" << std::endl;
    }
    else {
        std::cerr << "Read error: " << UA_StatusCode_name(status) << std::endl;
    }

    // Wait loop to keep the client active
    while (true)
    {
        std::cout << "Press Enter to exit..." << std::endl;
        std::cin.get();
    }

    // Cleanup resources
    UA_Variant_clear(&value);
    UA_Client_disconnect(client);
    UA_Client_delete(client);
    return 0;
}
