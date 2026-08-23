#pragma once

#include <cxxabi.h>
#include <atomic>
#include <cstdlib>
#include <iostream>
#include <mutex>
#include <string>
#include <typeinfo>
#include <unordered_map>
#include <vector>

class ObjectGraphTracer {
public:
    struct Node {
        std::string type;
        std::string label;
    };

    static ObjectGraphTracer& instance() {
        static ObjectGraphTracer t;
        return t;
    }

    template <typename T>
    std::size_t add_node(const T* ptr, const std::string& label = "") {
        const std::size_t id = next_id_++;
        std::lock_guard<std::mutex> lock(mu_);
        nodes_[id] = Node{demangle(typeid(T).name()), label};
        ptr_to_id_[reinterpret_cast<std::uintptr_t>(ptr)] = id;
        return id;
    }

    void add_edge(const void* parent, const void* child, const std::string& label = "") {
        std::lock_guard<std::mutex> lock(mu_);
        edges_.push_back(Edge{id_for_unlocked(parent), id_for_unlocked(child), label});
    }

    void dump_dot(std::ostream& os) const {
        std::lock_guard<std::mutex> lock(mu_);
        os << "digraph ObjectGraph {\n";
        os << "  node [shape=box, fontname=\"Helvetica\"];\n";

        for (const auto& [id, node] : nodes_) {
            os << "  n" << id << " [label=\""
               << escape(node.type);
            if (!node.label.empty()) {
                os << "\\n" << escape(node.label);
            }
            os << "\"];\n";
        }

        for (const auto& e : edges_) {
            if (e.from == 0 || e.to == 0) continue;
            os << "  n" << e.from << " -> n" << e.to;
            if (!e.label.empty()) {
                os << " [label=\"" << escape(e.label) << "\"]";
            }
            os << ";\n";
        }

        os << "}\n";
    }

private:
    struct Edge {
        std::size_t from;
        std::size_t to;
        std::string label;
    };

    static std::string demangle(const char* name) {
        int status = 0;
        char* realname = abi::__cxa_demangle(name, nullptr, nullptr, &status);
        std::string out = (status == 0 && realname) ? realname : name;
        std::free(realname);
        return out;
    }

    static std::string escape(const std::string& s) {
        std::string out;
        out.reserve(s.size());
        for (char c : s) {
            if (c == '"' || c == '\\') out.push_back('\\');
            out.push_back(c);
        }
        return out;
    }

    std::size_t id_for_unlocked(const void* ptr) const {
        auto it = ptr_to_id_.find(reinterpret_cast<std::uintptr_t>(ptr));
        return it == ptr_to_id_.end() ? 0 : it->second;
    }

    mutable std::mutex mu_;
    std::atomic<std::size_t> next_id_{1};
    std::unordered_map<std::size_t, Node> nodes_;
    std::unordered_map<std::uintptr_t, std::size_t> ptr_to_id_;
    std::vector<Edge> edges_;
};
