package lintuhaaste.ui.list

import android.icu.text.DateFormat
import android.os.Bundle
import android.util.Log
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Toast
import androidx.fragment.app.Fragment
import androidx.fragment.app.activityViewModels
import com.mob2022.lintuhaaste.R
import lintuhaaste.data.ListViewModel
import lintuhaaste.databinding.FragmentAddBinding
import java.util.*

class AddFragment : Fragment() {

    private val listViewModel: ListViewModel by activityViewModels()
    private var _binding: FragmentAddBinding? = null
    private lateinit var selectedDate: String

    // This property is only valid between onCreateView and
    // onDestroyView.
    private val binding get() = _binding!!

    override fun onCreateView(
        inflater: LayoutInflater,
        container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View {

        _binding = FragmentAddBinding.inflate(inflater, container, false)
        val root: View = binding.root

        // Get current date and set as default
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


        binding.buttonSave.setOnClickListener {

            // Add a new species and navigate back
            if (binding.editSpecies.text.isNotEmpty()) {
                listViewModel.addNew(binding, selectedDate)
                Toast.makeText(
                    context, "${binding.editSpecies.text} lisätty" , Toast.LENGTH_SHORT).show()

                listViewModel.navController.navigate(R.id.action_navigation_add_to_navigation_list)

            // If no species is given, show error message
            } else {
                Toast.makeText(
                    context, "Syötä havaittu lintulaji!" , Toast.LENGTH_SHORT).show()
            }

        }

        return root
    }

    override fun onDestroyView() {
        super.onDestroyView()
        _binding = null
    }
}