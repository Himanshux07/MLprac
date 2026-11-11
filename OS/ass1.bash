
#!/bin/bash

file="addressbook.txt"

while true
do
    echo "-----------------------------"
    echo "       ADDRESS BOOK"
    echo "-----------------------------"
    echo "1. Create Address Book"
    echo "2. View Address Book"
    echo "3. Insert Record"
    echo "4. Delete Record"
    echo "5. Modify Record"
    echo "6. Exit"
    echo "-----------------------------"

    read -p "Enter your choice: " ch

    case $ch in

    1)
        touch "$file"
        echo "Address book created successfully."
        ;;

    2)
        echo "----- Address Book -----"

        if [ ! -f "$file" ]; then
            echo "Address book does not exist."
        elif [ -s "$file" ]; then
            cat "$file"
        else
            echo "Address book is empty."
        fi
        ;;

    3)
        if [ ! -f "$file" ]; then
            echo "Create address book first!"
        else
            read -p "Enter Name: " name
            read -p "Enter Phone: " phone
            read -p "Enter Email: " email

            echo "$name | $phone | $email" >> "$file"

            echo "Record inserted successfully."
        fi
        ;;

    4)
        if [ ! -f "$file" ]; then
            echo "Address book does not exist."
        else
            read -p "Enter Name to delete: " name

            if grep -Fq "$name |" "$file"; then
                grep -Fv "$name |" "$file" > temp.txt
                mv temp.txt "$file"
                echo "Record deleted successfully."
            else
                echo "Record not found."
            fi
        fi
        ;;

    5)
        if [ ! -f "$file" ]; then
            echo "Address book does not exist."
        else
            read -p "Enter Name to modify: " oldname

            if grep -Fq "$oldname |" "$file"; then
                read -p "Enter New Name: " newname
                read -p "Enter New Phone: " newphone
                read -p "Enter New Email: " newemail

                grep -Fv "$oldname |" "$file" > temp.txt
                echo "$newname | $newphone | $newemail" >> temp.txt
                mv temp.txt "$file"

                echo "Record modified successfully."
            else
                echo "Record not found."
            fi
        fi
        ;;

    6)
        echo "Exiting..."
        exit 0
        ;;

    *)
        echo "Invalid choice!"
        ;;

    esac

    echo
done
