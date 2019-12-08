from typing import *


def dutch_flag_partition_linear(arr: List[int], pivot_index: int) -> NoReturn:
    pivot = arr[pivot_index]
    next_less: int = 0
    next_equal: int = 0
    for i in range(len(arr)):
        if arr[i] < pivot:
            arr[i], arr[next_equal] = arr[next_equal], arr[i]
            arr[next_less], arr[next_equal] = arr[next_equal], arr[next_less]
            next_equal += 1
            next_less += 1
        elif arr[i] == pivot:
            arr[i], arr[next_equal] = arr[next_equal], arr[i]
            next_equal += 1


def dutch_flag_partition_convergent(arr: List[int], pivot_index: int) -> NoReturn:
    pivot = arr[pivot_index]
    next_less: int = 0
    next_equal: int = 0
    next_greater: int = len(arr) - 1
    while next_equal <= next_greater:
        if arr[next_equal] < pivot:
            arr[next_equal], arr[next_less] = arr[next_less], arr[next_equal]
            next_less += 1
            next_equal += 1
        elif arr[next_equal] == pivot:
            next_equal += 1
        else:
            arr[next_equal], arr[next_greater] = arr[next_greater], arr[next_equal]
            next_greater -= 1
