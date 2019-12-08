### dutch_flag_partition_linear
This approach separates the array into 3 categories: less than pivot, equal to pivot, and greater than pivot + 
unknown. This guarantees that once all the elements that are less than or equal to the pivot are in the correct place,
all the elements greater than the pivot will also be in the correct place because it is the only category remaining. At
each step, we place the elements in either the less than pivot section, equal to pivot section, or leave them in the 
greater than pivot/unprocessed section.

### dutch_flag_partition_convergent
This approach separates the array into 4 categories: less than pivot, equal to pivot, greater than pivot, or unknown. At
each step we place the current element (at next_equal) into its proper category.