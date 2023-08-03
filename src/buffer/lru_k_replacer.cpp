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

LRUKReplacer::LRUKReplacer(size_t num_frames, size_t k) : k_(k), replacer_size_(num_frames) {

}

auto LRUKReplacer::Evict(frame_id_t *frame_id) -> bool {

}

void LRUKReplacer::RecordAccess(frame_id_t frame_id) {

}

void LRUKReplacer::SetEvictable(frame_id_t frame_id, bool set_evictable) {

}

void LRUKReplacer::Remove(frame_id_t frame_id) {

}

auto LRUKReplacer::Size() -> size_t { return curr_size_; }

}  // namespace bustub
