#include <iostream>
#include <boost/asio.hpp>
#include <memory>
#include <array>

namespace asio = boost::asio;

class EchoSession : public std::enable_shared_from_this<EchoSession> {
private:
    asio::ip::tcp::socket socket;
    std::array<char, 2056> buffer;
public:
    EchoSession(asio::ip::tcp::socket p_socket) 
        : socket(std::move(p_socket)) {}
    
    void start() {
        read();
    }
    
    void read() {
        auto self = shared_from_this();
        socket.async_read_some(asio::buffer(buffer),
            [this, self](boost::system::error_code ec, size_t bytes) {
                if (ec) {
                    if (ec != asio::error::eof) {
                        std::cerr << "Read error: " << ec.message() << "\n";
                    }
                    return;
                }
                write(bytes);
            });
    }
    
    void write(size_t bytes) {
        auto self = shared_from_this();
        asio::async_write(socket, asio::buffer(buffer, bytes),
            [this, self](boost::system::error_code ec, size_t) {
                if (ec) {
                    std::cerr << "Write error: " << ec.message() << "\n";
                    return;
                }
                read();
            });
    }
};

class Server {
private:
    asio::ip::tcp::acceptor acceptor;
    asio::strand<asio::io_context::executor_type> accept_strand;

    void do_accept() {
        acceptor.async_accept(asio::bind_executor(accept_strand,
            [this](boost::system::error_code ec, asio::ip::tcp::socket socket) {
                if (ec) {
                    std::cerr << "Accept error: " << ec.message() << "\n";
                } else {
                    std::make_shared<EchoSession>(std::move(socket))->start();
                }
                do_accept();
            }));
    }

public:
    Server(asio::io_context& io, unsigned short port)
        : acceptor(io, {asio::ip::tcp::v4(), port}),
          accept_strand(asio::make_strand(io)) 
    {
        do_accept();
    }
};

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <port>\n";
        return 1;
    }

    try {
        const unsigned short port = static_cast<unsigned short>(std::atoi(argv[1]));
        asio::io_context io;
        
        auto work = asio::require(io.get_executor(), asio::execution::outstanding_work.tracked);
        
        Server server(io, port);
        
        asio::thread_pool pool(10);
        for (int i = 0; i < 10; ++i) {
            asio::post(pool, [&io] {
                while(!io.stopped()) {
                    try {
                        io.run();
                    } catch (const std::exception& e) {
                        io.restart();
                        std::cerr << "Thread exception: " << e.what() << "\n";
                    }
                }
            });
        }
        
        pool.join();
        
    } catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << "\n";
        return 1;
    }
    
    return 0;
}