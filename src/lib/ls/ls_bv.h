/***
 * Bitwuzla: Satisfiability Modulo Theories (SMT) solver.
 *
 * Copyright (C) 2022 by the authors listed in the AUTHORS file at
 * https://github.com/bitwuzla/bitwuzla/blob/main/AUTHORS
 *
 * This file is part of Bitwuzla under the MIT license. See COPYING for more
 * information at https://github.com/bitwuzla/bitwuzla/blob/main/COPYING
 */

#ifndef BZLA__LS_LS_BV_H
#define BZLA__LS_LS_BV_H

#include <optional>
#include <string>

#include "ls/ls.h"

namespace bzla {

class BitVector;
class BitVectorDomain;

namespace ls {

class BitVectorNode;

class LocalSearchBV : public LocalSearch<BitVector>
{
 public:
  /**
   * Constructor.
   * @param max_nprops   The maximum number of propagations to perform. Zero
   *                     if unlimited.
   * @param max_nupdates The maximum number of cone updates to perform. Zero
   *                     if unlimited.
   * @param seed         The initial seed for the random number generator.
   * @param log_level       The log level, 0 to disable log messages.
   * @param verbosity_level The verbosity level, 0 to disable verbose messages.
   * @param stats_prefix The prefix to use for statistis.
   * @param statistics   The associated statistics object, will be nullptr
   *                     when used outside of Bitwuzla.
   */
  LocalSearchBV(uint64_t max_nprops,
                uint64_t max_nupdates,
                uint32_t seed                   = 27644437,
                uint32_t log_level              = 0,
                uint32_t verbosity_level        = 0,
                const std::string& stats_prefix = "lib::ls::bv::",
                util::Statistics* statistics    = nullptr);
  /**
   * Create node.
   * @param kind     The node kind.
   * @param size     The bit-vector size of the node.
   * @param children The children, empty for NodeKind::CONST.
   * @param indices  The set of indices, empty for non-indexed nodes.
   * @param symbol   Optionally, a symbol string identifying the node, only
   *                 used for logging.
   * @return The index of the created node.
   */
  uint64_t mk_node(NodeKind kind,
                   uint64_t size,
                   const std::vector<uint64_t>& children    = {},
                   const std::vector<uint64_t>& indices     = {},
                   const std::optional<std::string>& symbol = std::nullopt);
  /**
   * Create node.
   * @param kind     The node kind.
   * @param domain   The associated bit-vector domain.
   * @param children The children, empty for NodeKind::CONST.
   * @param indices  The set of indices, empty for non-indexed nodes.
   * @param symbol   Optionally, a symbol string identifying the node, only
   *                 used for logging.
   * @return The index of the created node.
   */
  uint64_t mk_node(NodeKind kind,
                   const BitVectorDomain& domain,
                   const std::vector<uint64_t>& children    = {},
                   const std::vector<uint64_t>& indices     = {},
                   const std::optional<std::string>& symbol = std::nullopt);
  /**
   * Create const node.
   * @param assignment The current assignment of the node.
   * @param domain     The associated bit-vector domain.
   * @param symbol     Optionally, a symbol string identifying the node, only
   *                   used for logging.
   * @return The index of the created node.
   */
  uint64_t mk_node(const BitVector& assignment,
                   const BitVectorDomain& domain,
                   const std::optional<std::string>& symbol = std::nullopt);

  /**
   * Invert node given by id.
   * @param id The id of the node to invert.
   * @return The inverted node.
   */
  uint64_t invert_node(uint64_t id);

  /**
   * Get the domain of the node given by id.
   * @param id The id of the node to query.
   * @return The domain of the node given by id.
   */
  const BitVectorDomain& get_domain(uint64_t id) const;

  /** Fix domain bit of given node at index 'idx' to 'value'. */
  void fix_bit(uint64_t id, uint32_t idx, bool value);

  void compute_bounds(Node<BitVector>* node) override;

 private:
  /**
   * Helper for creating a node.
   * @param kind     The node kind.
   * @param size     The bit-vector size of the node.
   * @param children The children, empty for NodeKind::CONST.
   * @param indices  The set of indices, empty for non-indexed nodes.
   * @param symbol   Optionally, a symbol string identifying the node, only
   *                 used for logging.
   * @return The index of the created node.
   */
  uint64_t _mk_node(NodeKind kind,
                    uint64_t size,
                    const std::vector<uint64_t>& children    = {},
                    const std::vector<uint64_t>& indices     = {},
                    const std::optional<std::string>& symbol = std::nullopt);
  /**
   * Helper for creating a node.
   * @param kind     The node kind.
   * @param domain   The associated bit-vector domain.
   * @param children The children, empty for NodeKind::CONST.
   * @param indices  The set of indices, empty for non-indexed nodes.
   * @param symbol   Optionally, a symbol string identifying the node, only
   *                 used for logging.
   * @return The index of the created node.
   */
  uint64_t _mk_node(NodeKind kind,
                    const BitVectorDomain& domain,
                    const std::vector<uint64_t>& children    = {},
                    const std::vector<uint64_t>& indices     = {},
                    const std::optional<std::string>& symbol = std::nullopt);
  /**
   * Get node by id.
   * @param id The node id.
   * @return The node with the given id.
   */
  BitVectorNode* get_node(uint64_t id) const;
  /**
   * Helper for computing bounds of children of root inequalities.
   * @param root The root node.
   * @param pos The position of the child to update, -1 for updating all
   *            children.
   */
  void update_bounds_aux(BitVectorNode* root, int32_t pos);
};

}  // namespace ls
}  // namespace bzla
#endif
