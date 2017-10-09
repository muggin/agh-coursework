from django.shortcuts import render
 
def home(request):
    return render(request, 'index.html', {})

'''
TO DO:
Email after creating new listing
Inline listing form
User groups
Custom login form
Billing service


'''