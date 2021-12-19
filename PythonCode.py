import re
import string
import os.path
from os import path


#Description:
#       To call this function, pass the function name into the CallProcedure function.
#Example:
#       callProcedure("CountAll");
#Output:
#       Returns a list of all unique items in CS210, and prints all of their occurrances.
#Return:
#       None
def CountObj():
    #Read file for inputs
    text = open("CS210_Project_Three_Input_File.txt", "r")

    #dictionary for counting inputs from the input text file
    dictionary = dict()

    #Loop to check for all inputs
    for line in text:
    #remove extra spaces and lower case all characters to get a valid total if users input is non standardized
        line = line.strip()
        word = line.lower()
        
        if word in dictionary:
            #Increment total if word is already in the dictionary to output total
            dictionary[word] = dictionary[word] + 1
        else:
            #If the word isn't alreayd in dictionary, add a new dict item and add 1 to it's value'
            dictionary[word] = 1

    #output all items in the dictionary as capitalized versions of themselves
    for key in list (dictionary.keys()):
        print(key.capitalize(), ":", dictionary[key])

    text.close()



#Description:
#       To call this function, pass this function into the CallIntFunc function along with the desired search term.
#Example:
#       callIntFunc("CountInstances", searchTerm);
#Output:
#       Returns the number of occurrances of the desired search term.
#Return:
#       int wordCount
def CountTotals(searchTerm):
    searchTerm = searchTerm.lower()
    #lowercase all values from input to get a better total in case user input is non standardized
    text = open("CS210_Project_Three_Input_File.txt", "r")

    #Empty variable to get total count later on
    wordCount = 0

    #Loop to check all items in the file
    for line in text:
        line = line.strip()
        word = line.lower()
        #remove extra spaces and lower case all characters to get a valid total if users input is non standardized

        if word == searchTerm:
            #Increase by one if the word already exists given the user input
            wordCount += 1

    #Output total
    return wordCount

    text.close()



#Count the number of appearances for each item, then write to frequency.dat

#Description:
#       To call this function, pass this function into the CallProcedure function.
#Example:
#       callProcedure("CollectData");
#Output:
#       Returns a a document (frequency.dat) with each unique word and the number of times that word occurs..
#Return:
#       frequency.dat
def CollectData():
    text = open("CS210_Project_Three_Input_File.txt", "r")

    #Open file
    frequency = open("frequency.dat", "w")
    #dictionary for getting totals
    dictionary = dict()

    for line in text:
        #loop for checking all items
        line = line.strip()
        word = line.lower()
        #remove extra spaces and lower case all characters to get a valid total if users input is non standardized
        
        if word in dictionary:
            #Increase by one if item is in dictionary already
            dictionary[word] = dictionary[word] + 1
        else:
            #If the word isn't alreayd in dictionary, add a new dict item and add 1 to it's value'
            dictionary[word] = 1

    for key in list (dictionary.keys()):
        #Output dictionary item and key as strings as it cannot be integers based on testing
        frequency.write(str(key.capitalize()) + " " + str(dictionary[key]) + "\n")

    text.close()
    frequency.close()
