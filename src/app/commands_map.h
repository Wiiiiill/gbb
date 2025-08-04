/*
** GB BASIC
**
** Copyright (C) 2023-2025 Tony Wang, all rights reserved
**
** For the latest info, see https://paladin-t.github.io/kits/gbb/
*/

#ifndef __COMMANDS_MAP_H__
#define __COMMANDS_MAP_H__

#include "commands_grouped.h"
#include "commands_paintable.h"
#include "commands_paintable2d.h"

/*
** {===========================================================================
** Map commands
*/

namespace Commands {

namespace Map {

#if GBBASIC_EDITOR_PAINTABLE2D_ENABLED
namespace PaintableBase = Commands::Paintable2D;
#else /* GBBASIC_EDITOR_PAINTABLE2D_ENABLED */
namespace PaintableBase = Commands::Paintable;
#endif /* GBBASIC_EDITOR_PAINTABLE2D_ENABLED */

class Pencil : public PaintableBase::Pencil {
public:
	Pencil();
	virtual ~Pencil() override;

	static Command* create(void);
	static void destroy(Command* ptr);
};

class Line : public PaintableBase::Line {
public:
	Line();
	virtual ~Line() override;

	static Command* create(void);
	static void destroy(Command* ptr);
};

class Box : public PaintableBase::Box {
public:
	Box();
	virtual ~Box() override;

	static Command* create(void);
	static void destroy(Command* ptr);
};

class BoxFill : public PaintableBase::BoxFill {
public:
	BoxFill();
	virtual ~BoxFill() override;

	static Command* create(void);
	static void destroy(Command* ptr);
};

class Ellipse : public PaintableBase::Ellipse {
public:
	Ellipse();
	virtual ~Ellipse() override;

	static Command* create(void);
	static void destroy(Command* ptr);
};

class EllipseFill : public PaintableBase::EllipseFill {
public:
	EllipseFill();
	virtual ~EllipseFill() override;

	static Command* create(void);
	static void destroy(Command* ptr);
};

class Fill : public PaintableBase::Fill {
public:
	Fill();
	virtual ~Fill() override;

	static Command* create(void);
	static void destroy(Command* ptr);
};

class Replace : public PaintableBase::Replace {
public:
	Replace();
	virtual ~Replace() override;

	static Command* create(void);
	static void destroy(Command* ptr);
};

class Stamp : public PaintableBase::Stamp {
public:
	Stamp();
	virtual ~Stamp() override;

	static Command* create(void);
	static void destroy(Command* ptr);
};

class Rotate : public PaintableBase::Rotate {
public:
	Rotate();
	virtual ~Rotate() override;

	static Command* create(void);
	static void destroy(Command* ptr);
};

class Flip : public PaintableBase::Flip {
public:
	Flip();
	virtual ~Flip() override;

	static Command* create(void);
	static void destroy(Command* ptr);
};

class Cut : public PaintableBase::Cut {
public:
	Cut();
	virtual ~Cut() override;

	static Command* create(void);
	static void destroy(Command* ptr);
};

class Paste : public PaintableBase::Paste {
public:
	Paste();
	virtual ~Paste() override;

	static Command* create(void);
	static void destroy(Command* ptr);
};

class Delete : public PaintableBase::Delete {
public:
	Delete();
	virtual ~Delete() override;

	static Command* create(void);
	static void destroy(Command* ptr);
};

class SetName : public Command {
public:
	GBBASIC_PROPERTY(std::string, name)

	GBBASIC_PROPERTY(std::string, old)

public:
	SetName();
	virtual ~SetName() override;

	GBBASIC_CLASS_TYPE('S', 'N', 'M', 'M')

	virtual unsigned type(void) const override;

	virtual const char* toString(void) const override;

	virtual Command* redo(Object::Ptr obj, int argc, const Variant* argv) override;
	using Command::redo;
	virtual Command* undo(Object::Ptr obj, int argc, const Variant* argv) override;
	using Command::undo;

	virtual SetName* with(const std::string &n);

	virtual Command* exec(Object::Ptr obj, int argc, const Variant* argv) override;
	using Command::exec;

	static Command* create(void);
	static void destroy(Command* ptr);
};


class SwitchLayer : public Layered::Layered {
public:
	typedef std::function<void(int, bool)> LayerEnabledSetter;

public:
	GBBASIC_PROPERTY_READONLY(LayerEnabledSetter, setLayerEnabled)
	GBBASIC_PROPERTY_READONLY(bool, enabled)

	GBBASIC_PROPERTY_READONLY(bool, old)

public:
	SwitchLayer();
	virtual ~SwitchLayer() override;

	GBBASIC_CLASS_TYPE('S', 'W', 'L', 'M')

	virtual unsigned type(void) const override;

	virtual const char* toString(void) const override;

	virtual Command* redo(Object::Ptr obj, int argc, const Variant* argv) override;
	using Command::redo;
	virtual Command* undo(Object::Ptr obj, int argc, const Variant* argv) override;
	using Command::undo;

	virtual SwitchLayer* with(LayerEnabledSetter set);
	virtual SwitchLayer* with(bool enabled_);
	using Layered::Layered::with;

	virtual Command* exec(Object::Ptr obj, int argc, const Variant* argv) override;
	using Command::exec;

	static Command* create(void);
	static void destroy(Command* ptr);
};

class ToggleMask : public PaintableBase::Pencil {
public:
	ToggleMask();
	virtual ~ToggleMask() override;

	GBBASIC_CLASS_TYPE('T', 'G', 'M', 'M')

	virtual unsigned type(void) const override;

	static Command* create(void);
	static void destroy(Command* ptr);
};

class Resize : public Layered::Layered {
public:
	GBBASIC_PROPERTY(Math::Vec2i, size)

	GBBASIC_PROPERTY(int, bytes)
	GBBASIC_PROPERTY(Bytes::Ptr, old)
	GBBASIC_PROPERTY(int, attributesBytes)
	GBBASIC_PROPERTY(Bytes::Ptr, oldAttributes)

public:
	Resize();
	virtual ~Resize() override;

	GBBASIC_CLASS_TYPE('R', 'S', 'Z', 'M')

	virtual unsigned type(void) const override;

	virtual const char* toString(void) const override;

	virtual Command* redo(Object::Ptr obj, int argc, const Variant* argv) override;
	using Command::redo;
	virtual Command* undo(Object::Ptr obj, int argc, const Variant* argv) override;
	using Command::undo;

	virtual Resize* with(const Math::Vec2i &size);
	using Layered::Layered::with;

	virtual Command* exec(Object::Ptr obj, int argc, const Variant* argv) override;
	using Command::exec;

	static Command* create(void);
	static void destroy(Command* ptr);
};

class SetOptimized : public Command {
public:
	GBBASIC_PROPERTY(bool, optimized)

	GBBASIC_PROPERTY(bool, old)

public:
	SetOptimized();
	virtual ~SetOptimized() override;

	GBBASIC_CLASS_TYPE('O', 'P', 'T', 'M')

	virtual unsigned type(void) const override;

	virtual const char* toString(void) const override;

	virtual Command* redo(Object::Ptr obj, int argc, const Variant* argv) override;
	using Command::redo;
	virtual Command* undo(Object::Ptr obj, int argc, const Variant* argv) override;
	using Command::undo;

	virtual SetOptimized* with(bool optimized_);

	virtual Command* exec(Object::Ptr obj, int argc, const Variant* argv) override;
	using Command::exec;

	static Command* create(void);
	static void destroy(Command* ptr);
};

class Import : public Layered::Layered {
public:
	GBBASIC_PROPERTY(::Map::Ptr, map)
	GBBASIC_PROPERTY(bool, hasAttributes)
	GBBASIC_PROPERTY(::Map::Ptr, attributes)

	GBBASIC_PROPERTY(int, bytes)
	GBBASIC_PROPERTY(Bytes::Ptr, old)
	GBBASIC_PROPERTY(bool, oldHasAttributesFilled)
	GBBASIC_PROPERTY(bool, oldHasAttributes)
	GBBASIC_PROPERTY(int, attributesBytes)
	GBBASIC_PROPERTY(Bytes::Ptr, oldAttributes)

public:
	Import();
	virtual ~Import() override;

	GBBASIC_CLASS_TYPE('I', 'M', 'P', 'M')

	virtual unsigned type(void) const override;

	virtual const char* toString(void) const override;

	virtual Command* redo(Object::Ptr obj, int argc, const Variant* argv) override;
	using Command::redo;
	virtual Command* undo(Object::Ptr obj, int argc, const Variant* argv) override;
	using Command::undo;

	virtual Import* with(const ::Map::Ptr &map_, bool hasAttrib, const ::Map::Ptr &attrib);
	virtual Import* with(const ::Map::Ptr &data, int layer);
	using Layered::Layered::with;

	virtual Command* exec(Object::Ptr obj, int argc, const Variant* argv) override;
	using Command::exec;

	static Command* create(void);
	static void destroy(Command* ptr);
};

class BeginGroup : public Grouped::BeginGroup {
public:
	BeginGroup();
	virtual ~BeginGroup() override;

	GBBASIC_CLASS_TYPE('B', 'G', 'G', 'M')

	virtual unsigned type(void) const override;

	virtual const char* toString(void) const override;

	static Command* create(void);
	static void destroy(Command* ptr);
};

class EndGroup : public Grouped::EndGroup {
public:
	EndGroup();
	virtual ~EndGroup() override;

	GBBASIC_CLASS_TYPE('E', 'D', 'G', 'M')

	virtual unsigned type(void) const override;

	virtual const char* toString(void) const override;

	static Command* create(void);
	static void destroy(Command* ptr);
};

class Reference : public Grouped::Reference {
public:
	Reference();
	virtual ~Reference() override;

	GBBASIC_CLASS_TYPE('R', 'E', 'F', 'M')

	virtual unsigned type(void) const override;

	virtual const char* toString(void) const override;

	static Command* create(void);
	static void destroy(Command* ptr);
};

}

}

/* ===========================================================================} */

#endif /* __COMMANDS_MAP_H__ */
