from django.forms import ModelForm
from modules.accommodations.models import Accommodation


class ListingForm(ModelForm):
    class Meta:
        model = Accommodation
        fields = '__all__'


class AccommodationForm(ModelForm):
    class Meta:
        model = Accommodation
        fields = '__all__'