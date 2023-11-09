package lintuhaaste.ui.list

import android.annotation.SuppressLint
import android.os.Bundle
import androidx.fragment.app.Fragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Toast
import androidx.fragment.app.activityViewModels
import lintuhaaste.R
import lintuhaaste.data.ListViewModel
import lintuhaaste.databinding.FragmentDetailsBinding


class DetailsFragment : Fragment() {

    private val listViewModel: ListViewModel by activityViewModels()
    private var _binding: FragmentDetailsBinding? = null

    private val binding get() = _binding!!

    @SuppressLint("SetTextI18n")
    override fun onCreateView(
        inflater: LayoutInflater,
        container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View {

        _binding = FragmentDetailsBinding.inflate(inflater, container, false)
        val root: View = binding.root

        // Show information of the sighting on the screen
        binding.dateText.text = "Havaittu: ${listViewModel.currentSighting.getDate()}"
        binding.speciesText.text = listViewModel.currentSighting.getSpecies()
        binding.locationText.text = "Havaintopaikka: ${listViewModel.currentSighting.getLocation()}"
        binding.notesText.text = "Muistiinpanot: ${listViewModel.currentSighting.getNotes()}"

        // If "Delete" button is tapped, infrom user to tap and hold to to verify
        binding.buttonDelete.setOnClickListener {
            Toast.makeText(
                context, "Paina nappulaa pitkään poistaaksesi havainnon" , Toast.LENGTH_SHORT).show()
        }

        // Listen on the Delete button (tap and hold activity)
        binding.buttonDelete.setOnLongClickListener {
            val species = listViewModel.currentSighting.getSpecies()
            if (listViewModel.deleteSighting()) {
                Toast.makeText(
                    context, "$species poistettu listalta" , Toast.LENGTH_SHORT).show()
                listViewModel.navController.navigateUp()
            } else {
                Toast.makeText(
                    context, "Ongelma poistossa. Mitään ei poistettu", Toast.LENGTH_SHORT
                ).show()
            }
            return@setOnLongClickListener true
        }

        binding.buttonEdit.setOnClickListener {
            listViewModel.navController.navigate(R.id.action_detailsFragment_to_editFragment)
        }


        // Inflate the layout for this fragment
        return root
    }
}