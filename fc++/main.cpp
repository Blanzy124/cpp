#include <websocketpp/websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/websocketpp/client.hpp>

#include <iostream>

typedef websocketpp::client<websocketpp::config::asio_client> client;

void on_message(websocketpp::connection_hdl, client::message_ptr msg) {
    std::cout << "Mensaje recibido: " << msg->get_payload() << std::endl;
}

int main() {
    client c;

    try {
        c.set_access_channels(websocketpp::log::alevel::none);
        c.init_asio();
        c.set_message_handler(&on_message);

        websocketpp::lib::error_code ec;
        auto con = c.get_connection("ws://echo.websocket.org", ec);

        if (ec) {
            std::cout << "Error de conexión: " << ec.message() << std::endl;
            return 1;
        }

        c.connect(con);
        c.run();
    } catch (std::exception& e) {
        std::cout << "Excepción: " << e.what() << std::endl;
    }

    return 0;
}
