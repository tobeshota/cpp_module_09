#include <gtest/gtest.h>

#include "PmergeMe.hpp"

// ---------- template function ---------- //

template<typename Container>
Container returnSortedSeq(const Container &seq) {
	Container sortedSeq(seq);
	std::sort(sortedSeq.begin(), sortedSeq.end());
	return sortedSeq;
}

template<typename Container>
void validateSortable(Container input) {
	const Container &expect = returnSortedSeq(input);
	const Container &actual = mergeInsertionSort(input);
	EXPECT_EQ(expect, actual);
}

// ---------- test macro ---------- //

TEST(SortableTest, UniqueElem) {
	validateSortable(std::vector<int>{3, 5, 9, 7, 4});
}

TEST(SortableTest, DuplicateElem) {
	validateSortable(std::vector<int>{5, 5, 5});
}

TEST(SortableTest, AlreadySorted) {
	validateSortable(std::vector<int>{2, 4, 6});
}

TEST(SortableTest, Empty) {
	validateSortable(std::vector<int>{});
}

TEST(SortableTest, Only1) {
	validateSortable(std::vector<int>{42});
}
