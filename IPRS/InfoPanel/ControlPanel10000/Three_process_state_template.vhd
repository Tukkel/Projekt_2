library ieee;
use ieee.std_logic_1164.all;

entity three_process_fsm_template is
	<port_declarations>
end three_process_fsm_template;

architecture three_processes of three_process_fsm_template is
	type state is (enumeration_of_state_names);
	signal present_state, next_state : state;
begin

state_reg: process (clk)
begin
	if rising_edge(clk) then
		if reset_bar = '0' then
			present_state <= <initial_state>;
		else
			present_state <= next_state;
		end if;
	end if;
end process;

outputs: process (present_state, <inputs>);
begin
	case present_state is
	-- one case branch required for each state
	when <state_value_i> =>
		if <input_condition_1> then
		-- assignments to outputs
		elsif <input_condition_2> then
		-- assignments to outputs
		else
		-- assignments to outputs;
		end if;

	...

	-- default branch
	when others =>
	-- assignments to outputs

	end case;
end process;

nxt_state: process (present_state, <inputs>);
begin
	case present_state is

	-- one case branch required for each state
		when <state_value_i> =>
			if <input_condition_1> then
			-- assignment to next_state
			elsif <input_condition_2> then
			-- assignment to next_state
			else
			-- assignment to next_state
			end if;

		--...

		-- default branch
		when others =>
		-- assign initial_state to next_state

	end case;
end process;

end three_processes;