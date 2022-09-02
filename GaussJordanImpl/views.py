import json

from django.shortcuts import render
from django.http import HttpResponse
from django.views.decorators.csrf import csrf_exempt
from subprocess import Popen, PIPE
import os

@csrf_exempt
def mainPage(request):
    if request.method == 'POST':
        form_data = json.loads(request.body.decode())
        final_matrix = form_data['matrix']
        matrix_array = ""
        print(final_matrix)
        for i in range(form_data['rows']):
            for j in range(form_data['columns']):
                matrix_array = matrix_array + " " + str(final_matrix[i][j])

        root_path = os.getcwd()
        new_matrix = [os.path.join(root_path, 'GaussJordanImpl\\templates\\GaussJordanImpl\\static\\gaussJordan.exe'),
                      str(form_data['rows']), str(form_data['columns'])]
        new_matrix = new_matrix + matrix_array.strip().split(' ')
        process = Popen(new_matrix, stdout=PIPE)
        (output, err) = process.communicate()
        return HttpResponse(output.decode("ascii"))
    else:
        return render(request, 'GaussJordanImpl/welcome.html')
