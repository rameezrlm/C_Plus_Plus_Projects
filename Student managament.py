print("       =======Menu=======        ")
print("Press 'S': Add more 5 records in the file with existing file format.")
print("Press 'P': Print all records on console.  ")
print("Press 'D': Department wise searching.")
print("Press 'R': Write all the record into another file for backup.")
print("Press 'X': exit.")

choice = input("Enter a character: ")
if(choice=='S' or choice=='s'):
     with open("input.txt","r") as f:
        for i in range(6):
            string1=input("Enter Name: ")
            age=input("Enter Age: ")
            string2 = input("Enter Department: ")
            final = string1 + " ," + age + " ," + string2
            f.write(final);
elif(choice=='p' or choice=='P'):
    with open("input.txt","r") as f:
        data = f.read()
        print(data)
elif(choice=='D' or choice=='d'):
   dept = input("Enter department: ")
   f = open("input.txt","r")
   waste = f.readline()
   data = f.readlines()
   for i in data:
       field = i.split(',')
       if(field[2]==" "+dept):
           print("Name: ",field[0])
           print("Age: ",field[1])
           print("Department: ",field[2])
elif(choice=='R' or choice=='r'):
    with open("input.txt","r") as f:
        data = f.read()
        with open("another.txt","w") as f1:
            f1.write(data)
elif(choice=='X' or choice=='x'):
    print("Program Ends!")