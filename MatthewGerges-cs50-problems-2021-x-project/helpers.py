
'''
vector1 = input("First Vector: ")
vector2 = input("Second Vector: ")
'''
'''
def main():
    components1 = componentcount(vector1)
    
    components2 = componentcount(vector2)
    
    if (components1 != components2):
        print("Both vectors must have the same number of components")
        # return
        
    setup = setvectors(vector1, vector2, components1)
'''
    
# Dot prod(1)
from flask import redirect, render_template, request, session


def componentcount(vector):
    componentnumber = 0
    for c in vector:
        if c != "," and c!=" ":
            componentnumber += 1
            
    return componentnumber
            
def setvectors(v1, v2, num):
    crossprod = 0
    component_amount = 0
    vi = []
    vf = []
    for c in v1:
        if c != "," and c!=" ":
            vi.append(c)
    for s in v2:
        if s != "," and s!=" ":
            vf.append(s)
        #v[0] * p[0] + v[1] *p[2]
    
    vi = [int(i) for i in vi]
    vf = [int(i) for i in vf]
    
    #print(vi)
    #print(vf)
    
    crossprod1 = (vi[1] * vf[2] - vi[2] * vf[1]) 
    crossprod2 = (vi[2] * vf[0] - vi[0] * vf[2])
    crossprod3 = (vi[0] * vf[1] - vi[1] * vf[0])
    print("cross prod is", crossprod1, ",", crossprod2, ",", crossprod3)

def setvector(vect):
    vectlist = []
    for c in vect:
        if c != "," and c != " ":
            vectlist.append(int(c))
            #print(c)
            #print(vect)
    
    #vectlist = [int(i) for i in vectlist]
    
    return vectlist
        
        
def apology(message, code=400):
    """Render message as an apology to user."""
    def escape(s):
        """
        Escape special characters.

        https://github.com/jacebrowning/memegen#special-characters
        """
        for old, new in [("-", "--"), (" ", "-"), ("_", "__"), ("?", "~q"),
                         ("%", "~p"), ("#", "~h"), ("/", "~s"), ("\"", "''")]:
            s = s.replace(old, new)
        return s
    return render_template("apology.html", top=code, bottom=escape(message)), code