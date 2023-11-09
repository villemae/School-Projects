package lintuhaaste.ui.list

import android.icu.text.DateFormat
import android.os.Bundle
import android.util.Log
import androidx.fragment.app.Fragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Toast
import androidx.fragment.app.activityViewModels
import lintuhaaste.data.ListViewModel
import lintuhaaste.databinding.FragmentEditBinding
import java.util.*

class EditFragment : Fragment() {

    private val listViewModel: ListViewModel by activityViewModels()
    private var _binding: FragmentEditBinding? = null
    private lateinit var selectedDate: String

    // This property is only valid between onCreateView and
    // onDestroyView.
    private val binding get() = _binding!!

    override fun onCreateView(
        inflater: LayoutInflater,
        container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View {
        _binding = FragmentEditBinding.inflate(inflater, container, false)
        val root: View = binding.root

        binding.speciesText.setText(listViewModel.currentSighting.getSpecies())

        binding.editLocation.setText(listViewModel.currentSighting.getLocation())
        binding.editNotes.setText(listViewModel.currentSighting.getNotes())

        // Set the current date as default in calendar
        val calendar = Calendar.getInstance()
        val dateFormatter = DateFormat.getDateInstance(DateFormat.MEDIUM)
        selectedDate = dateFormatter.format(calendar.time)
        Log.d("AddFragment", selectedDate)

        // Calendar view date change listener
        binding.editDate.setOnDateChangeListener { view, year, month, dayOfMonth ->
            // set the calendar date as calendar view selected date
            calendar.set(year,month,dayOfMonth)

            // set this date as calendar view selected date
            binding.editDate.date = calendar.timeInMillis

            // format the calendar view selected date
            selectedDate = dateFormatter.format(calendar.time)
            Log.d("AddFragment", selectedDate)
        }


        // Update the sighting info
        binding.buttonSave.setOnClickListener {
            listViewModel.updateSighting(binding, selectedDate)
                Toast.makeText(
                    context, "Muokkaus onnistui" , Toast.LENGTH_SHORT).show()
            listViewModel.navController.navigateUp()

        }

        return root
    }

    override fun onDestroyView() {
        super.onDestroyView()
        _binding = null
    }
}