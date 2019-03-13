#include "Trigger.h"
namespace Syntax {
Trigger::Trigger(std::unique_ptr<Token> t, std::function<void(void)> action) : t(std::move(t)), action(action) {}
void Trigger::Process(Cursor & cursor)
{
	t->Process(cursor);
	if (t->Success())
		action();
}
bool Trigger::Success()
{
	return t->Success();
}
}