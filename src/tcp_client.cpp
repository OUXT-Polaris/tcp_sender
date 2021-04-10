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

#include <tcp_sender/tcp_client.hpp>

#include <string>

namespace tcp_sender
{
TcpClient::TcpClient(
  boost::asio::io_service & io_service, const rclcpp::Logger & logger)
: io_service_(io_service),
  socket_(io_service_),
  logger_(logger)
{
}

void TcpClient::connect()
{
  socket_.async_connect(
    boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 31400),
    boost::bind(&TcpClient::onConnect, this, boost::asio::placeholders::error));
}

void TcpClient::send(const std::string & message)
{
  boost::asio::async_write(
    socket_,
    boost::asio::buffer(message),
    boost::bind(
      &TcpClient::onSend, this,
      boost::asio::placeholders::error,
      boost::asio::placeholders::bytes_transferred));
}

void TcpClient::onSend(const boost::system::error_code & error, size_t)
{
  if (error) {
    RCLCPP_ERROR(logger_, "send failed : " + error.message());
  } else {
    RCLCPP_INFO(logger_, "send correct!");
  }
}

void TcpClient::onConnect(const boost::system::error_code & error)
{
  if (error) {
    RCLCPP_ERROR(logger_, "connect failed : " + error.message());
  } else {
    RCLCPP_INFO(logger_, "connected");
  }
}
}  // namespace tcp_sender
