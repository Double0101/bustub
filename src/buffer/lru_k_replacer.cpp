//===----------------------------------------------------------------------===//
//
//                         BusTub
//
// lru_k_replacer.cpp
//
// Identification: src/buffer/lru_k_replacer.cpp
//
// Copyright (c) 2015-2022, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#include "buffer/lru_k_replacer.h"

namespace bustub {

LRUKReplacer::LRUKReplacer(size_t num_frames, size_t k) : replacer_size_(num_frames), timer_(k, num_frames) {
  evictable_.resize(replacer_size_, false);
}

auto LRUKReplacer::Evict(frame_id_t *frame_id) -> bool {
  if (Size() == 0) {
    return false;
  }
  size_t evict = 0;
  size_t earliest;
  size_t et;
  bool access_k;
  bool ak;
  bool batter;
  while (evict < replacer_size_ && !evictable_[evict]) {
    ++evict;
  }
  access_k = timer_.BackwardK(evict, &earliest);
  for (size_t i = evict + 1; i < replacer_size_; ++i) {
    if (!evictable_[i]) {
      continue;
    }
    batter = false;
    ak = timer_.BackwardK(i, &et);
    if (et < earliest) {
      if (ak == access_k) {
        batter = true;
      }
    } else if (access_k && !ak) {
      batter = true;
    }
    if (batter) {
      access_k = ak;
      evict = i;
      earliest = et;
    }
  }
  *frame_id = evict;
  return true;
}

void LRUKReplacer::RecordAccess(frame_id_t frame_id) {
  BUSTUB_ASSERT(replacer_size_ > (size_t) frame_id, "Invaild frame_id");
  timer_.FrameAccess(frame_id);
  SetEvictable(frame_id, false);
}

void LRUKReplacer::SetEvictable(frame_id_t frame_id, bool set_evictable) {
  BUSTUB_ASSERT(replacer_size_ > (size_t) frame_id, "Invaild frame_id");
  if (set_evictable != evictable_[frame_id]) {
    curr_size_ += (evictable_[frame_id] - set_evictable);
  }
}

void LRUKReplacer::Remove(frame_id_t frame_id) {
  BUSTUB_ASSERT(replacer_size_ > (size_t) frame_id, "Invaild frame_id");
  SetEvictable(frame_id, true);
  timer_.Remove(frame_id);
}

auto LRUKReplacer::Size() -> size_t { return curr_size_; }

LRUKReplacer::Timer::Timer(size_t k, size_t no_replacer) : k_(k), no_replacer_(no_replacer) {
  last_k_time_.resize(no_replacer_, nullptr);
}

void LRUKReplacer::Timer::FrameAccess(frame_id_t frame_id) {
  BUSTUB_ASSERT(no_replacer_ > (size_t) frame_id, "Invaild frame_id");
  std::shared_ptr<std::list<size_t>> frame_last_k = last_k_time_[frame_id];
  if (frame_last_k == nullptr) {
    frame_last_k = std::make_shared<std::list<size_t>>();
    last_k_time_[frame_id] = frame_last_k;
  }
  if (frame_last_k->size() == k_) {
    frame_last_k->pop_front();
  }
  frame_last_k->push_back(current_timestamp_++);
}

auto LRUKReplacer::Timer::BackwardK(frame_id_t frame_id, size_t *tm) -> bool {
  BUSTUB_ASSERT(no_replacer_ > (size_t) frame_id, "Invaild frame_id");
  std::shared_ptr<std::list<size_t>> frame_last_k = last_k_time_[frame_id];
  if (frame_last_k == nullptr) {
    *tm = 0;
    return false;
  }
  *tm = frame_last_k->front();
  return frame_last_k->size() == k_;
}

auto LRUKReplacer::Timer::Remove(bustub::frame_id_t frame_id) -> void {
  BUSTUB_ASSERT(no_replacer_ > (size_t) frame_id, "Invaild frame_id");
  last_k_time_[frame_id] = nullptr;
}

}  // namespace bustub
