Term_clear()

local call_stack = {}
local i = 2

while 1 do
	local info = debug.getinfo(i, 'n')
	if not info then break end

	-- insert at the front
	table.insert(call_stack, 1, info.name)

	i = i + 1
end

for index, name in call_stack do
	if index ~= 'n' then
		text_out(TERM_WHITE, string.format("%s\n", name))
	end
end

text_out(TERM_WHITE, "\n")

local i = 1

while 1 do
	local name
	local value

	name, value = debug.getlocal(2, i)
	if not name then break end

	text_out(TERM_WHITE, string.format("'%s' : %s\n", name, tostring(value)))
	i = i + 1
end

