#pragma once

#include <cstdint>
#include <memory>

#include "envoy/network/connection.h"
#include "envoy/network/filter.h"
#include "envoy/network/listen_socket.h"
#include "envoy/network/listener.h"
#include "envoy/ssl/context.h"

namespace Envoy {
namespace Network {

/**
 * Abstract connection handler.
 */
class ConnectionHandler {
public:
  virtual ~ConnectionHandler() = default;

  /**
   * @return uint64_t the number of active connections owned by the handler.
   */
  virtual uint64_t numConnections() PURE;

  /**
   * Adds a listener to the handler.
   * @param config listener configuration options.
   */
  virtual void addListener(ListenerConfig& config) PURE;

  /**
   * Remove listeners using the listener tag as a key. All connections owned by the removed
   * listeners will be closed.
   * @param listener_tag supplies the tag passed to addListener().
   */
  virtual void removeListeners(uint64_t listener_tag) PURE;

  /**
   * Stop listeners using the listener tag as a key. This will not close any connections and is used
   * for draining.
   * @param listener_tag supplies the tag passed to addListener().
   */
  virtual void stopListeners(uint64_t listener_tag) PURE;

  /**
   * Stop all listeners. This will not close any connections and is used for draining.
   */
  virtual void stopListeners() PURE;

  /**
   * Disable all listeners. This will not close any connections and is used to temporarily
   * stop accepting connections on all listeners.
   */
  virtual void disableListeners() PURE;

  /**
   * Enable all listeners. This is used to re-enable accepting connections on all listeners
   * after they have been temporarily disabled.
   */
  virtual void enableListeners() PURE;
};

using ConnectionHandlerPtr = std::unique_ptr<ConnectionHandler>;

/**
 * fixfix
 */
class BalancedConnectionHandler {
public:
  virtual ~BalancedConnectionHandler() = default;

  virtual uint64_t tag() PURE;
  virtual uint64_t numConnections() PURE;
  virtual void incNumConnections() PURE;
  virtual void post(Network::ConnectionSocketPtr&& socket) PURE;
};

/**
 * fixfix
 */
class ConnectionBalancer {
public:
  virtual ~ConnectionBalancer() = default;

  /**
   *
   */
  virtual void registerHandler(BalancedConnectionHandler& handler) PURE;

  /**
   *
   */
  virtual void unregisterHandler(BalancedConnectionHandler& handler) PURE;

  /**
   *
   */
  enum class BalanceConnectionResult { Rebalanced, Continue };
  virtual BalanceConnectionResult
  balanceConnection(Network::ConnectionSocketPtr&& socket,
                    BalancedConnectionHandler& current_handler) PURE;
};

} // namespace Network
} // namespace Envoy
