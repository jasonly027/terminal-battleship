#ifndef BATTLESHIP_TS_QUEUE_H
#define BATTLESHIP_TS_QUEUE_H
#pragma once

#include <cstddef>
#include <deque>
#include <mutex>
#include <utility>

namespace battleship {
template <typename T> class tsqueue {
public:
    tsqueue() = default;
    tsqueue(const tsqueue<T> &) = delete;
    virtual ~tsqueue() { clear(); }

    // Get front
    const T &front() {
        std::scoped_lock lock(muxQueue_);
        return deqQueue_.front();
    }

    // Get back
    const T &back() {
        std::scoped_lock lock(muxQueue_);
        return deqQueue_.back();
    }

    // Append to back
    void push_back(const T &item) {
        std::scoped_lock lock(muxQueue_);
        deqQueue_.emplace_back(std::move(item));
    }

    // Prepend to front
    void push_front(const T &item) {
        std::scoped_lock lock(muxQueue_);
        deqQueue_.emplace_front(std::move(item));
    }

    // Check if empty
    bool empty() {
        std::scoped_lock lock(muxQueue_);
        return deqQueue_.empty();
    }

    // Get size of container
    size_t size() {
        std::scoped_lock lock(muxQueue_);
        return deqQueue_.size();
    }

    // Empty container
    void clear() {
        std::scoped_lock lock(muxQueue_);
        deqQueue_.clear();
    }

    // Pop and return back
    T pop_back() {
        std::scoped_lock lock(muxQueue_);
        auto t = std::move(deqQueue_.back());
        return t;
    }

    // Pop and return front
    T pop_front() {
        std::scoped_lock lock(muxQueue_);
        auto t = std::move(deqQueue_.front());
        return t;
    }

protected:
    std::mutex muxQueue_;
    std::deque<T> deqQueue_;
};
} // namespace battleship

#endif