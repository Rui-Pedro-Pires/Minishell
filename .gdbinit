set auto-load safe-path /

break heardoc_checker.c:28

run

set $STR=heardoc_read[count_struc->counter]

while ($STR)
	print $STR
	set $STR=heardoc_read[count_struc->counter]
	continue
end