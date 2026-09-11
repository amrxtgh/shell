  ## How to improve it

  Prioritize improvements in this order:

  1. Support external commands

     Implement fork(), execvp(), and waitpid() so commands such as echo, grep, vim, and gcc work.

  2. Improve the parser

     The current parser only splits on spaces. Add support for:
      - Tabs and multiple spaces
      - Quoted arguments, such as echo "hello world"
      - Escaped characters
      - Better handling of long input
      - Clear errors when the argument limit is exceeded

  3. Fix correctness issues

     In builtin_cat(), fgetc() should be stored in an int, not a char, because EOF is an integer value.
     See src/commands/commands.c:71.

     Also add return statuses so commands can report success or failure to the shell.

  4. Add pipes and redirection

     Support common shell syntax:

     ls | grep .c
     echo hello > output.txt
     cat < input.txt

  5. Replace the large if/else chain

     Use a command table containing command names and function pointers. This will make adding commands
     easier and keep src/handlers/command_handler.c cleaner.

  6. Improve built-in commands

     Add support for:
      - cd .., cd ~, and cd -
      - Multiple arguments for ls, cat, and mkdir
      - Options such as mkdir -p
      - Better error messages
      - Hidden files and file metadata for ls

  7. Add tests

     Create automated tests for parsing, cd, pwd, mkdir, touch, cat, invalid commands, and quoted
     arguments.

  8. Improve documentation

     The README.md currently only contains the project title. Add:
      - Project description
      - Supported commands
      - Build instructions
      - Usage examples
      - Planned features
      - Known limitations

  9. Clean up the build configuration

     CMakeLists.txt declares both C and C++, but the project only uses C. Change:

      project(shell LANGUAGES C)

  The best next milestone would be: external command execution plus a proper parser. That will turn this
  from a built-in command demo into a genuinely usable shell.
