#pragma once

#include "IAllocator.h"
#include <mutex>

class StandardAllocator : public IAllocator
{
public:
	StandardAllocator() = default;
	~StandardAllocator() override = default;

	// 복사 대입 금지
	StandardAllocator(const StandardAllocator&) = delete;
	StandardAllocator& operator=(const StandardAllocator&) = delete;

	/**
	 * @param size		할당할 메모리 크기		(바이트)
	 * @param alignment 정렬 바이트				(기본: 포인터 정렬)
	 * @param debugName 디버깅용 태그 이름		(선택적)
	 * @return void*	할당된 메모리 포인터	(실패 시 nullptr 반환)
	 */
	void* Allocate(
		size_t size, size_t alignment = alignof(void*),
		const char* debugName = nullptr) override;

	/**
	 * @param p		해제할 메모리 포인터
	 * @param size	해제할 메모리 크기 (할당 시 사용된 값)
	 */
	void Deallocate(void* p, size_t size, size_t alignmnet) override;

	void* Reallocate(
		void* p, size_t oldSize, size_t newSize,
		size_t		alignment = alignof(void*),
		const char* debugName = nullptr) override;

	size_t GetTotalAllocatedBytes() const override;
	size_t GetLiveAllocationCount() const override;

	bool Owns(void* p) const override;

private:
	// const 함수에서 뮤텍스를 잠그기 위해 mutable 사용
	mutable std::mutex Mutex;				// 스레드 안정성을 위한 뮤텍스
	size_t			   AllocatedSize = 0;	// 총 할당된 바이트 수
	size_t			   AllocationCount = 0; // 현재 할당된 블록 수
};
