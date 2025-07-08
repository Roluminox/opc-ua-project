#include <iostream>
#include <open62541/client.h>
#include <open62541/client_config_default.h>
#include <open62541/client_highlevel.h>

int main() {
    UA_Client* client = UA_Client_new();
    UA_ClientConfig_setDefault(UA_Client_getConfig(client));

    // Connexion au serveur (localhost:4840)
    UA_StatusCode status = UA_Client_connect(client, "opc.tcp://localhost:4840");
    if (status != UA_STATUSCODE_GOOD) {
        std::cerr << "Erreur de connexion: " << UA_StatusCode_name(status) << std::endl;
        UA_Client_delete(client);
        return 1;
    }

    // Lecture de la variable "temperature"
    UA_Variant value;
    UA_Variant_init(&value);

    UA_NodeId nodeId = UA_NODEID_STRING(1, (char*)"temperature");
    status = UA_Client_readValueAttribute(client, nodeId, &value);
    if (status == UA_STATUSCODE_GOOD && UA_Variant_hasScalarType(&value, &UA_TYPES[UA_TYPES_DOUBLE])) {
        std::cout << "Temperature: " << *(UA_Double*)value.data << " °C" << std::endl;
    }
    else {
        std::cerr << "Erreur de lecture: " << UA_StatusCode_name(status) << std::endl;
    }

    while (true)
    {
        std::cout << "Press Enter to exit..." << std::endl;
        std::cin.get();
    }

    UA_Variant_clear(&value);
    UA_Client_disconnect(client);
    UA_Client_delete(client);
    return 0;
}
