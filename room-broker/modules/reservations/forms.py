from modules.reservations.models import Reservation

__author__ = 'O10'
from django.forms import ModelForm, DateInput


class EForm(ModelForm):
    class Meta:
        model = Reservation
        widgets = {'date': DateInput(attrs={'class': 'datepicker'})}