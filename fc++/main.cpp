#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <iostream>
#include <string>

namespace beast = boost::beast;
namespace websocket = beast::websocket;
namespace net = boost::asio;
using tcp = net::ip::tcp;

int main() {
    try {
        std::string host = "echo.websocket.org";
        std::string port = "80";
        std::string message = "Hola desde Boost.Beast!";

        net::io_context ioc;
        tcp::resolver resolver{ioc};
        websocket::stream<tcp::socket> ws{ioc};

        auto const results = resolver.resolve(host, port);
        net::connect(ws.next_layer(), results);

        ws.handshake(host, "/");
        ws.write(net::buffer(message));

        beast::flat_buffer buffer;
        ws.read(buffer);

        std::cout << "Respuesta del servidor: " << beast::make_printable(buffer.data()) << std::endl;

        ws.close(websocket::close_code::normal);
    } catch (std::exception const& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
