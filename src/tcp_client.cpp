// Copyright (c) 2021 OUXT Polaris
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <string>
#include <tcp_sender/tcp_client.hpp>

namespace tcp_sender
{
TcpClient::TcpClient(boost::asio::io_service & io_service, const rclcpp::Logger & logger)
: io_service_(io_service), socket_(io_service_), logger_(logger)
{
}

void TcpClient::connect(const std::string & address, const int & port)
{
  socket_.connect(
    boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(address), port));
}

bool TcpClient::send(const std::string & message)
{
  boost::system::error_code error;
  boost::asio::write(socket_, boost::asio::buffer(message), error);
  if (error) {
    RCLCPP_ERROR(logger_, error.message().c_str());
    return false;
  }
  return true;
}

bool TcpClient::send(const uint8_t * message, size_t length)
{
  boost::system::error_code error;
  boost::asio::write(socket_, boost::asio::buffer(message, length), error);
  if (error) {
    RCLCPP_ERROR(logger_, error.message().c_str());
    return false;
  }
  return true;
}

}  // namespace tcp_sender
