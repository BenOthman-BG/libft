*This project has been created as part of the 42 curriculum by obenyhy.*

# Libft

## Description

**Libft** is the first project of the 42 curriculum. The goal is to build your own C static library, `libft.a`, a collection of general-purpose functions that will be reused in later school projects.

The project teaches how the standard C library works internally by reimplementing it, and builds a solid foundation in memory management, string handling, pointers and linked lists.

The library is split into three parts:

1. **Libc functions**: reimplementations of standard functions, with the same prototypes and behavior as the originals, prefixed with `ft_`.
2. **Additional functions**: utilities that are not in libc or exist in a different form (string manipulation, number conversion, file descriptor output).
3. **Linked list functions**: a small API to manipulate singly linked lists built on the `t_list` structure.

### Library content

#### Part 1 - Libc functions

| Category | Functions |
|---|---|
| Character classification | `ft_isalpha`, `ft_isdigit`, `ft_isalnum`, `ft_isascii`, `ft_isprint` |
| Character conversion | `ft_toupper`, `ft_tolower` |
| String functions | `ft_strlen`, `ft_strlcpy`, `ft_strlcat`, `ft_strchr`, `ft_strrchr`, `ft_strncmp`, `ft_strnstr`, `ft_atoi` |
| Memory functions | `ft_memset`, `ft_bzero`, `ft_memcpy`, `ft_memmove`, `ft_memchr`, `ft_memcmp` |
| Allocation (uses `malloc`) | `ft_calloc`, `ft_strdup` |

Notes:
- The character classification functions return `1` if the character matches the class and `0` otherwise.
- `ft_calloc` returns a unique pointer that can be passed to `free()` when `nmemb` or `size` is `0`.
- The `restrict` qualifier is not used in the prototypes.

#### Part 2 - Additional functions

| Function | Description |
|---|---|
| `ft_substr` | Allocates and returns a substring of `s`, starting at index `start`, of maximum length `len`. |
| `ft_strjoin` | Allocates and returns the concatenation of `s1` and `s2`. |
| `ft_strtrim` | Allocates and returns a copy of `s1` without the characters in `set` at the beginning and the end. |
| `ft_split` | Splits `s` using the delimiter `c`; returns a NULL-terminated array of independently allocated strings. |
| `ft_itoa` | Allocates and returns the string representation of an integer (negative numbers handled). |
| `ft_strmapi` | Applies `f(index, char)` to each character of `s` and returns a new string with the results. |
| `ft_striteri` | Applies `f(index, &char)` to each character of `s`, allowing in-place modification. |
| `ft_putchar_fd` | Writes a character to the given file descriptor. |
| `ft_putstr_fd` | Writes a string to the given file descriptor. |
| `ft_putendl_fd` | Writes a string followed by a newline to the given file descriptor. |
| `ft_putnbr_fd` | Writes an integer to the given file descriptor. |

#### Part 3 - Linked list

The following structure is declared in `libft.h`:

```c
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;
```

| Function | Description |
|---|---|
| `ft_lstnew` | Creates a new node with the given content; `next` is set to `NULL`. |
| `ft_lstadd_front` | Adds a node at the beginning of the list. |
| `ft_lstsize` | Counts the number of nodes in the list. |
| `ft_lstlast` | Returns the last node of the list. |
| `ft_lstadd_back` | Adds a node at the end of the list. |
| `ft_lstdelone` | Frees a node's content with `del`, then frees the node (not the next one). |
| `ft_lstclear` | Deletes and frees the given node and all its successors, then sets the list pointer to `NULL`. |
| `ft_lstiter` | Applies `f` to the content of each node. |
| `ft_lstmap` | Applies `f` to each node's content and builds a new list; uses `del` to clean up on allocation failure. |

### Technical choices

- Written in C, following the 42 Norm.
- Compiled with `cc -Wall -Wextra -Werror`.
- No global variables; helper functions are declared `static`.
- The library archive is created with `ar` (`libtool` is forbidden).
- No unnecessary relinking in the Makefile.
- All heap memory is freed when needed; no memory leaks.

## Instructions

### Compilation

At the root of the repository:

```bash
make        # builds libft.a
make clean  # removes object files
make fclean # removes object files and libft.a
make re     # fclean + all
```

The Makefile provides the rules `$(NAME)`, `all`, `clean`, `fclean` and `re`.

### Usage

Include the header in your code:

```c
#include "libft.h"
```

Then compile your program and link it with the library:

```bash
cc -Wall -Wextra -Werror main.c libft.a -o my_program
```

Example:

```c
#include "libft.h"

int	main(void)
{
	char	**words;
	int		i;

	words = ft_split("hello 42 world", ' ');
	if (!words)
		return (1);
	i = 0;
	while (words[i])
	{
		ft_putendl_fd(words[i], 1);
		free(words[i]);
		i++;
	}
	free(words);
	return (0);
}
```

## Resources

### References

- `man` pages (section 3) to understand each reimplemented libc function: `man 3 strlen`, `man 3 memmove`, etc.
- [linux.die.net](https://linux.die.net/): online man pages.
- [Valgrind](https://valgrind.org/): used to detect memory leaks and check memory management.
- General web searches (Google) for additional information on specific concepts.

### Use of AI

AI was used for the following tasks:

- **Understanding new concepts:** to help me understand new concepts, and to practice implementing them before moving on to solve the actual functions of the project.
- **Peer discussions:** to help me discuss and compare different perspectives on a new concept with my peers.
- **README:** to help build this README file.