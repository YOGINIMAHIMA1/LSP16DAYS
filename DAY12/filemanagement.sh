# Problem Statement: File Management Script with Functions and Arguments
 #Objective
 #Create a shell script that manages files in a specified directory. The script should include functions to perform the following tasks:

 # List all files in the directory.
 #Display the total number of files.
 # Copy a specified file to a new location.
 #Move a specified file to a new location.
 #Delete a specified file.



 #!/bin/bash

# Function to list all files in the directory
list_files() {
    local dir="$1"
    if [[ -d "$dir" ]]; then
        echo "Files in directory '$dir':"
        ls "$dir"
    else
        echo "Directory '$dir' does not exist."
    fi
}

# Function to display the total number of files in the directory
total_files() {
    local dir="$1"
    if [[ -d "$dir" ]]; then
        local count=$(ls -1 "$dir" | wc -l)
        echo "Total number of files in directory '$dir': $count"
    else
        echo "Directory '$dir' does not exist."
    fi
}

# Function to copy a specified file to a new location
copy_file() {
    local source="$1"
    local destination="$2"
    if [[ -f "$source" ]]; then
        cp "$source" "$destination"
        echo "File '$source' copied to '$destination'."
    else
        echo "File '$source' does not exist."
    fi
}

# Function to move a specified file to a new location
move_file() {
    local source="$1"
    local destination="$2"
    if [[ -f "$source" ]]; then
        mv "$source" "$destination"
        echo "File '$source' moved to '$destination'."
    else
        echo "File '$source' does not exist."
    fi
}

# Function to delete a specified file
delete_file() {
    local file="$1"
    if [[ -f "$file" ]]; then
        rm "$file"
        echo "File '$file' deleted."
    else
        echo "File '$file' does not exist."
    fi
}

# Main script logic
if [[ $# -lt 1 ]]; then
    echo "Usage: $0 <command> [arguments]"
    echo "Commands:"
    echo "  list <directory>                - List all files in the directory"
    echo "  total <directory>               - Display the total number of files in the directory"
    echo "  copy <source> <destination>     - Copy a specified file to a new location"
    echo "  move <source> <destination>     - Move a specified file to a new location"
    echo "  delete <file>                   - Delete a specified file"
    exit 1
fi

command="$1"
shift

case "$command" in
    list)
        list_files "$@"
        ;;
    total)
        total_files "$@"
        ;;
    copy)
        copy_file "$@"
        ;;
    move)
        move_file "$@"
        ;;
    delete)
        delete_file "$@"
        ;;
    *)
        echo "Invalid command: $command"
        echo "Usage: $0 <command> [arguments]"
        echo "Commands:"
        echo "  list <directory>                - List all files in the directory"
        echo "  total <directory>               - Display the total number of files in the directory"
        echo "  copy <source> <destination>     - Copy a specified file to a new location"
        echo "  move <source> <destination>     - Move a specified file to a new location"
        echo "  delete <file>                   - Delete a specified file"
        ;;
esac
