/**
 * @file server.cpp
 * @brief Simple OPC UA server exposing a "temperature" variable using open62541.
 *
 * This program creates an OPC UA server that exposes a single variable named "temperature".
 * The server runs until manually stopped.
 */
#include <iostream>
#include <open62541/server.h>
#include <open62541/server_config_default.h>
#include <open62541/plugin/log_stdout.h>

/**
 * @brief Main entry point for the OPC UA server.
 *
 * Creates and configures the server, adds a temperature variable node, and runs the server loop.
 * @return Exit status code (0 if successful, error code otherwise)
 */
int main()
{
    // Create and configure the OPC UA server
    UA_Server* server = UA_Server_new();
    UA_ServerConfig_setDefault(UA_Server_getConfig(server));

    // Define the attributes for the "temperature" variable
    UA_VariableAttributes attr = UA_VariableAttributes_default;
    UA_Double temp = 42.0; /**< Initial value for the temperature variable */
    UA_Variant_setScalar(&attr.value, &temp, &UA_TYPES[UA_TYPES_DOUBLE]);
    UA_NodeId tempNodeId = UA_NODEID_STRING(1, (char*)"temperature"); /**< NodeId for the temperature variable */
    UA_QualifiedName tempName = UA_QUALIFIEDNAME(1, (char*)"temperature"); /**< Qualified name for the variable */
    UA_NodeId parentNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER); /**< Parent folder */
    UA_NodeId variableType = UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE); /**< Variable type */

    // Add the "temperature" variable node to the server
    UA_Server_addVariableNode(server, tempNodeId, parentNodeId,
        UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
        tempName, variableType, attr, NULL, NULL);

    // Start the server main loop
    volatile UA_Boolean running = UA_TRUE;
    UA_StatusCode retval = UA_Server_run(server, &running);

    // Cleanup and shutdown
    UA_Server_delete(server);

    return (int)retval;
}
