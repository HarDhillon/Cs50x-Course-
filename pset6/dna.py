import sys
import csv
import pdb

if len(sys.argv) != 3:
    print("Usage: *Program Name* *name of a CSV file containing the STR counts* *name of a text file containing the DNA sequence*")

txt_file = open(sys.argv[2])
array = txt_file.read()

#this function looks for the largest number of times a dna string repeats itself back to back
def DNA_count(array, DNA):
    iDNA = len(DNA)
    sDNA = str(DNA)
    counter = 0
    highest = 0

    #how it works:if from X to Y the pattern matches what is put into the function, it goes into another loop
    #the other loop goes from the current position we are at, till the end, stepping the length of the pattern
    #if the next set from X to Y matches, it adds one to the counter and continues stepping. This continues till it no longer
    #matches and the counter is reset to 1, it then saves the highest number of times it was able to step
    for x in range(len(array)):
        if array[x : x + iDNA] == sDNA:
            for pos in range(x, len(array), iDNA):
                if array[pos : pos + iDNA] == sDNA:
                    counter = counter + 1
                    continue
                else:
                    if highest < counter:
                        highest = counter
                        counter = 0
                    break
        else:
            counter = 0
    return highest

def checker(dna_list, templist):
    target = len(dna_list)
    for x in range(len(templist)):
        #print("checking if", dna_list[x], "in", dna_dict)
        if dna_list[x] in dna_dict:
            #print("yes it is")
            #print("value in dict is", dna_dict[dna_list[x]])
            if templist[x] == dna_dict[dna_list[x]]:
                x += 1
            else:
                #print("values not matching")
                return False
            if x == target:
                return True

#putting the number of times the pattern occurs into a variable
agatc = DNA_count(array, "AGATC")
ttttttct = DNA_count(array, "TTTTTTCT")
aatg = DNA_count(array, "AATG")
tctag = DNA_count(array, 'TCTAG')
gata = DNA_count(array, 'GATA')
tatc = DNA_count(array, 'TATC')
gaaa = DNA_count(array, 'GAAA')
tctg = DNA_count(array, 'TCTG')

#making a dictionary that stores the DNA pattern, and the number of times it occurs in the file you feed in
dna_dict = {
"AGATC":str(agatc),
'TTTTTTCT':str(ttttttct),
'AATG':str(aatg),
'TCTAG':str(tctag),
'GATA':str(gata),
'TATC':str(tatc),
"GAAA":str(gaaa),
'TCTG':str(tctg)
}

templist=[]

#AGATC,TTTTTTCT,AATG,TCTAG,GATA,TATC,GAAA,TCTG
with open(sys.argv[1], 'r') as csv_file:
    reader = csv.reader(csv_file)

    # IMPORTANT NOTE: for .CSV files you are able to select all the columns under a header by changing .reader to .Dictreader then writing:
    # for X in row:
    #   column = row["*NAME OF COLUMN(the header)*"] e.g row["name"]
    for count, row in enumerate(reader):
        #print(row)
        if count == 0:
            dna_list = row[1:]
            #print(dna_list)
        else:
            templist = row[1:]
            #print(templist)
        if checker(dna_list, templist) == True:
            name = list()
            list = row[0:1]
            for item in list:
                print(item)
            quit()

print("No match")

#print("highest AGATC in row was:", agatc)
#print("highest TTTTTTCT in row was:", ttttttct)
#print("highest AATG in row was:", aatg)
#print("TCTAG was:", tctag)
#print("highest GATA:", gata)
#print("tatc was:", tatc)

txt_file.close()
