#include "API.h"

bool send_data(struct Settings* settings, LinkedList<long> data) {
    HTTPClient client;
    client.begin(settings->api->endpoint_uri);
    client.addHeader("Content-Type", "application/json");
    String json = parse_json(settings->api->username, settings->api->token, data);
    Serial.println(json);
    return true;
}

String parse_json(char* username, char* token, LinkedList<long> data) {
    String d = "";
    for(int i = 0; i < data.size(); i++) {
        d += String(data.get(i)) + ",";
    }
    d = d.substring(0, d.length() - 1);
    String json = "{\"username\":\"";
    json.concat(username);
    json.concat("\",\"token\":\"");
    json.concat(token);
    json.concat("\",\"data\":["),
    json.concat(d);
    json.concat("]}");
    return json;
}
