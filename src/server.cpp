#include <iostream>
#include <open62541/server.h>
#include <open62541/server_config_default.h>
#include <open62541/plugin/log_stdout.h>

int main()
{
    UA_Server* server = UA_Server_new();
    UA_ServerConfig_setDefault(UA_Server_getConfig(server));

    // Exemple : exposer une variable "temperature"
    UA_VariableAttributes attr = UA_VariableAttributes_default;
    UA_Double temp = 42.0;
    UA_Variant_setScalar(&attr.value, &temp, &UA_TYPES[UA_TYPES_DOUBLE]);
    UA_NodeId tempNodeId = UA_NODEID_STRING(1, (char*)"temperature");
    UA_QualifiedName tempName = UA_QUALIFIEDNAME(1, (char*)"temperature");
    UA_NodeId parentNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
    UA_NodeId variableType = UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE);

    UA_Server_addVariableNode(server, tempNodeId, parentNodeId,
        UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
        tempName, variableType, attr, NULL, NULL);

    volatile UA_Boolean running = UA_TRUE;
    UA_StatusCode retval = UA_Server_run(server, &running);

    UA_Server_delete(server);

    return (int)retval;
}
