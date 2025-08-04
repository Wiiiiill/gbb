/*
** GB BASIC
**
** Copyright (C) 2023-2025 Tony Wang, all rights reserved
**
** For the latest info, see https://paladin-t.github.io/kits/gbb/
*/

#ifndef __BYTES_H__
#define __BYTES_H__

#include "../gbbasic.h"
#include "object.h"
#include "stream.h"
#include <vector>

/*
** {===========================================================================
** Bytes
*/

/**
 * @brief Bytes streaming object.
 */
class Bytes : public Stream, public virtual Object {
public:
	typedef std::shared_ptr<Bytes> Ptr;

	typedef std::vector<Byte> Collection;

public:
	GBBASIC_CLASS_TYPE('B', 'Y', 'T', 'E')

	virtual const Byte* pointer(void) const = 0;
	virtual Byte* pointer(void) = 0;

	virtual const Collection* collection(void) const = 0;
	virtual Collection* collection(void) = 0;

	virtual const Byte &get(size_t index) const = 0;
	virtual void set(size_t index, Byte val) = 0;

	virtual bool insert(size_t pos, Byte val) = 0;
	virtual size_t remove(size_t pos, size_t count) = 0;
	virtual size_t removeFront(size_t count) = 0;
	virtual size_t removeBack(size_t pos) = 0;
	virtual Bytes* resize(size_t size) = 0;
	virtual void clear(void) = 0;

	static Bytes* create(void);
	static void destroy(Bytes* ptr);
};

/* ===========================================================================} */

#endif /* __BYTES_H__ */
