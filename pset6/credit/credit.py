from cs50 import get_string


#First Check if card is a valid number
#Check what bank the card belongs to

#Functions must be defined before using


#Checks if number is a valid credit card number
def LuhnsAlg(cardN):
    sum1, sum2 = 0, 0
    
    #allows to alternate between sum 1 and sum 2 starting from end of list
    posCheck = True
    
    
    #iterates through entire credit number and posCheck allows to get every other number
    for i in range(len(cardN), 0, -1):
        
        if posCheck == True:
            sum2 += int(cardN[i - 1])
            posCheck = False
        else:
            temp = 2 * int(cardN[i - 1])
            if temp // 10 == 0:
                sum1 += temp
            else:
                sum1 += (temp % 10) + (temp // 10)
            posCheck = True
    
    if (sum1 + sum2) % 10 == 0:
        return True
    else: 
        return False
        
        
    
#Checks if what bank and if card is a valid bank card  
def bankCheck(cardN):
    
    if len(cardN) == 15 and cardN[0:2] in ['34', '37']:
        return "AMEX"
    elif len(cardN) == 16 and cardN[0:2] in ['51', '52', '53', '54', '55']:
        return "MASTERCARD"
    elif (len(cardN) in [13, 16]) and cardN[0] == '4':
        return "VISA"
    else:
        return "INVALID"
        
        
        
credit = get_string("Number: ")
if LuhnsAlg(credit):
    print(bankCheck(credit))
else:
    print("INVALID")