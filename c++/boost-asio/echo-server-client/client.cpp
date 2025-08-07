#include <iostream>
#include <boost/asio.hpp>

int main(int argc, char *argv[]) {
try {
    
    if(argc != 3) {
        std::cerr << "Usage " << argv[0] << " <host name> <port number>";
    }
    
    std::string buffer;
    
    boost::asio::io_context io;
    
    boost::asio::ip::tcp::resolver resolver(io);
    boost::asio::ip::tcp::resolver::results_type endpoints = resolver.resolve(argv[1], argv[2]);
    boost::asio::ip::tcp::socket socket(io);
    boost::asio::connect(socket, endpoints);
    
    for(;;) {
        std::getline(std::cin, buffer);
        boost::asio::write(socket, boost::asio::buffer(buffer, sizeof(buffer)));
        boost::asio::read(socket, boost::asio::buffer(buffer, sizeof(buffer)));
        std::cout << buffer << '\n';
    }
    
    
} catch(const std::exception& e) {
    std::cout << "Faced error during execution: " << e.what();
    throw;
}

}